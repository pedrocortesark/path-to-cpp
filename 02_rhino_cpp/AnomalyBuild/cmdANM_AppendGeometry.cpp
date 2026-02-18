// cmdANM_AppendGeometry.cpp
//

#include "stdafx.h"
#include <filesystem>
#include <rhinoSdkFileMenu.h>
#include <iostream>
#include <string>
#include <set>

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//
// BEGIN ANM_AppendGeometry command
//

#pragma region ANM_AppendGeometry command

class CCommandANM_AppendGeometry : public CRhinoCommand
{
public:
	CCommandANM_AppendGeometry() = default;
	UUID CommandUUID() override
	{
		// {3b2afe81-f5f0-4626-ab18-6778bee60a89}
		static const GUID ANM_AppendGeometryCommand_UUID =
		{0x3b2afe81,0xf5f0,0x4626,{0xab,0x18,0x67,0x78,0xbe,0xe6,0x0a,0x89}};
		return ANM_AppendGeometryCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_AppendGeometry"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_AppendGeometry object
static class CCommandANM_AppendGeometry theANM_AppendGeometryCommand;


// Helper function to open a headless document
static unsigned int RhOpenHeadlessDocument(const wchar_t* pszPath)
{
  if (nullptr == pszPath || 0 == pszPath[0])
    return 0;

  if (!CRhinoFileUtilities::FileExists(pszPath))
    return 0;

  CRhinoOpenDocumentOptions options;
  options.SetCreateHeadless(true);
  options.SetMakeVisible(false);
  options.SetAddToMRU(false);
  options.SetUpdateDefaultDirectory(false);
  options.SetUserQueriesPermitted(false);
  options.SetFileReadingPlugInId(ON_nil_uuid, 0);

  return CRhinoDoc::OpenDocument(pszPath, &options);
}

// Ensure layer hierarchy PRE::CrvContour exists and return the index of CrvContour
static int EnsureContourLayer(CRhinoDoc* doc)
{
  if (!doc) return -1;

  // Try find by full path name first
  int full_index = doc->m_layer_table.FindLayerFromName(L"PRE::CrvContour", true, true, -1, -1);
  if (full_index >= 0)
    return full_index;

  // Ensure parent layer PRE exists
  int pre_index = doc->m_layer_table.FindLayerFromName(L"PRE", true, false, -1, -1);
  ON_UUID pre_id = ON_nil_uuid;
  if (pre_index < 0)
  {
    ON_Layer pre_layer;
    pre_layer.SetName(L"PRE");
    pre_layer.SetVisible(true);
    pre_index = doc->m_layer_table.AddLayer(pre_layer);
    if (pre_index < 0)
      return -1;
  }
  pre_id = doc->m_layer_table[pre_index].Id();

  // Create child CrvContour under PRE
  ON_Layer contour_layer;
  contour_layer.SetName(L"CrvContour");
  contour_layer.SetParentId(pre_id);
  contour_layer.SetVisible(true);
  int contour_index = doc->m_layer_table.AddLayer(contour_layer);
  if (contour_index < 0)
  {
    // As a fallback, try find again by name (full path)
    contour_index = doc->m_layer_table.FindLayerFromName(L"PRE::CrvContour", true, true, -1, -1);
  }
  return contour_index;
}

// Duplicate naked edge border curves from a brep and add to PRE::CrvContour layer
static int AddBrepBorderCurvesToContourLayer(CRhinoDoc* doc, const ON_Brep* brep)
{
  if (!doc || !brep)
    return 0;

  int contour_layer_index = EnsureContourLayer(doc);
  if (contour_layer_index < 0)
  {
    RhinoApp().Print(L"⚠️ Could not ensure PRE::CrvContour layer. Skipping border extraction.\n");
    return 0;
  }

  CRhinoObjectAttributes attr;
  attr.m_layer_index = contour_layer_index;

  int added = 0;

  // Collect naked edge curves (edges with only one trim)
  const int edge_count = brep->m_E.Count();
  for (int ei = 0; ei < edge_count; ++ei)
  {
    const ON_BrepEdge& edge = brep->m_E[ei];
    // Naked if it has a single trim
    if (edge.m_ti.Count() == 1)
    {
      ON_Curve* edge_curve = edge.DuplicateCurve();
      if (edge_curve)
      {
        // Add as normal curve object on contour layer
        if (doc->AddCurveObject(*edge_curve, &attr))
          ++added;
        delete edge_curve;
      }
    }
  }

  return added;
}

// Ensure layer PRE::TXTasCRV exists and return its index
static int EnsureTxtAsCrvLayer(CRhinoDoc* doc)
{
  if (!doc) return -1;

  // Try find by full path name first
  int full_index = doc->m_layer_table.FindLayerFromName(L"PRE::TXTasCRV", true, true, -1, -1);
  if (full_index >= 0)
    return full_index;

  // Ensure parent layer PRE exists
  int pre_index = doc->m_layer_table.FindLayerFromName(L"PRE", true, false, -1, -1);
  ON_UUID pre_id = ON_nil_uuid;
  if (pre_index < 0)
  {
    ON_Layer pre_layer;
    pre_layer.SetName(L"PRE");
    pre_layer.SetVisible(true);
    pre_index = doc->m_layer_table.AddLayer(pre_layer);
    if (pre_index < 0)
      return -1;
  }
  pre_id = doc->m_layer_table[pre_index].Id();

  // Create child TXTasCRV under PRE
  ON_Layer txt_layer;
  txt_layer.SetName(L"TXTasCRV");
  txt_layer.SetParentId(pre_id);
  txt_layer.SetVisible(true);
  int txt_layer_index = doc->m_layer_table.AddLayer(txt_layer);
  if (txt_layer_index < 0)
  {
    // As a fallback, try find again by name (full path)
    txt_layer_index = doc->m_layer_table.FindLayerFromName(L"PRE::TXTasCRV", true, true, -1, -1);
  }
  return txt_layer_index;
}

CRhinoCommand::result CCommandANM_AppendGeometry::RunCommand(const CRhinoCommandContext& context)
{
    // Variables
    // ON_wString layer_name = "Default";
    std::vector<ON_wString> target_layers = { 
        L"Crv_Plantilla_XY", 
        L"Leader", 
        L"Letra_Plantillas", 
        L"Axis"  // buscar por path completo
    };
	double move = 3000.0;

	// Start
    CRhinoDoc* doc = ::RhinoApp().ActiveDoc();

    // Prompt for folder path
    CRhinoGetString gs_folder;
    gs_folder.SetCommandPrompt(L"Enter the folder path containing .3dm files");
    gs_folder.AcceptNothing();
    gs_folder.GetString();
    if (gs_folder.CommandResult() != CRhinoCommand::success)
        return gs_folder.CommandResult();

    ON_wString folder_path = gs_folder.String();
    folder_path.TrimLeftAndRight();
    if (folder_path.IsEmpty()) {
        RhinoApp().Print(L"No folder path provided.\n");
        return CRhinoCommand::failure;
    }
    RhinoApp().Print(L"Found path: %s\n", static_cast<const wchar_t*>(folder_path));

    /** Prompt for layer name
    CRhinoGetString gs_layer;
    gs_layer.SetCommandPrompt(L"Enter the layer name to merge geometry from");
    gs_layer.AcceptNothing();
    gs_layer.GetString();
    if (gs_layer.CommandResult() != CRhinoCommand::success)
        return gs_layer.CommandResult();

    ON_wString layer_name = gs_layer.String();
    layer_name.TrimLeftAndRight();
    if (layer_name.IsEmpty()) {
        RhinoApp().Print(L"No layer name provided.\n");
        return CRhinoCommand::failure;
    }
    */
    
    //RhinoApp().Print(L"Layer to merge: %s\n", static_cast<const wchar_t*>(layer_name));

    std::wstring folder_path_wstr = static_cast<const wchar_t*>(folder_path);
    std::filesystem::path path(folder_path_wstr);
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
        RhinoApp().Print(L"❌ Folder does not exist or is not a directory.\n");
        return CRhinoCommand::failure;
    }

    int merged_files = 0;
    int file_index = 0;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
    {
        if (!entry.is_regular_file() || entry.path().extension() != L".3dm")
            continue;

        std::wstring file_path_str = entry.path().wstring();
        RhinoApp().Print(L"📂 Processing file: %s\n", file_path_str.c_str());

        unsigned int doc_sn = RhOpenHeadlessDocument(file_path_str.c_str());
        if (doc_sn == 0) {
            RhinoApp().Print(L"⚠️ Failed to open file: %s\n", file_path_str.c_str());
            continue;
        }
        CRhinoDoc* temp_doc = CRhinoDoc::FromRuntimeSerialNumber(doc_sn);
        if (!temp_doc) {
            RhinoApp().Print(L"⚠️ Could not get temp document for file: %s\n", file_path_str.c_str());
            CRhinoDoc::CloseDocument(doc_sn);
            continue;
        }

        // Find all target layer indices in the temp document
        std::set<int> target_layer_indices;
        for (const ON_wString lname : target_layers) {
            // Check if the layer name contains "::" (hierarchy separator)
            bool has_hierarchy = (lname.Find(L"::") >= 0);
            
            // If it has hierarchy, search by full path; otherwise search by local name
            int idx = temp_doc->m_layer_table.FindLayerFromName(
                static_cast<const wchar_t*>(lname), 
                has_hierarchy,  // fullpath_match = true if contains :
                false,          // case_sensitive
                -1, -1
            );
            
            if (idx >= 0)
            {
                target_layer_indices.insert(idx);
                RhinoApp().Print(L"   🔍 Found layer '%s' at index %d\n", static_cast<const wchar_t*>(lname), idx);
            }
            else
            {
                RhinoApp().Print(L"   ⚠️ Layer '%s' not found in file\n", static_cast<const wchar_t*>(lname));
            }
        }

        // Debug: Print all layer names in the document
        RhinoApp().Print(L"   📋 All layers in document:\n");
        for (int i = 0; i < temp_doc->m_layer_table.LayerCount(); ++i)
        {
            const CRhinoLayer& layer = temp_doc->m_layer_table[i];
            ON_wString full_path = layer.Name();
            RhinoApp().Print(L"      - [%d] %s\n", i, static_cast<const wchar_t*>(full_path));
        }

        if (target_layer_indices.empty()) {
            RhinoApp().Print(L"⚠️ None of the target layers found in file: %s\n", file_path_str.c_str());
            CRhinoDoc::CloseDocument(doc_sn);
            continue;
        }

        // Count total objects in the file
        int total_objects = 0;
        CRhinoObjectIterator count_it(
            doc_sn,
            CRhinoObjectIterator::undeleted_objects,
            CRhinoObjectIterator::active_and_reference_objects
        );
        for (CRhinoObject* obj = count_it.First(); obj != nullptr; obj = count_it.Next()) {
            ++total_objects;
        }
        RhinoApp().Print(L"Total objects in file: %d\n", total_objects);

        int copied_count = 0;
        CRhinoObjectIterator it(
            doc_sn,
            CRhinoObjectIterator::undeleted_objects,
            CRhinoObjectIterator::active_and_reference_objects
        );
        ON_Xform move_xform = ON_Xform::TranslationTransformation(ON_3dVector(move * file_index, 0.0, 0.0));
        for (CRhinoObject* obj = it.First(); obj != nullptr; obj = it.Next()) {
            if (target_layer_indices.count(obj->Attributes().m_layer_index) > 0) {
                CRhinoObjectAttributes attr = obj->Attributes();

                // Get the source layer and build full path
                const CRhinoLayer& src_layer = temp_doc->m_layer_table[obj->Attributes().m_layer_index];
                ON_wString src_layer_name = src_layer.Name();
                
                // Build full layer path manually by walking up parent chain
                ON_wString src_layer_fullpath = src_layer_name;
                ON_UUID parent_id = src_layer.ParentLayerId();
                while (!ON_UuidIsNil(parent_id))
                {
                    // Find parent by iterating through layer table
                    int parent_layer_index = -1;
                    for (int li = 0; li < temp_doc->m_layer_table.LayerCount(); ++li)
                    {
                        if (temp_doc->m_layer_table[li].Id() == parent_id)
                        {
                            parent_layer_index = li;
                            break;
                        }
                    }
                    if (parent_layer_index < 0)
                        break;
                    
                    const CRhinoLayer& parent_layer = temp_doc->m_layer_table[parent_layer_index];
                    ON_wString parent_name = parent_layer.Name();
                    src_layer_fullpath = parent_name + L"::" + src_layer_fullpath;
                    parent_id = parent_layer.ParentLayerId();
                }

                // Debug: print what layer we're copying from
                RhinoApp().Print(L"      🔧 Copying object from layer: %s (index %d)\n", 
                    static_cast<const wchar_t*>(src_layer_fullpath), 
                    obj->Attributes().m_layer_index);

                // Find or create the layer in the main doc using full path
                int main_layer_index = doc->m_layer_table.FindLayerFromName(
                    static_cast<const wchar_t*>(src_layer_fullpath), 
                    true, // fullpath_match 
                    true, // case_sensitive
                    -1, -1
                );
                
                if (main_layer_index < 0)
                {
                    // Layer doesn't exist, need to create it with hierarchy
                    // Recursively ensure parent layers exist
                    ON_UUID main_parent_id = ON_nil_uuid;
                    ON_UUID temp_parent_id = src_layer.ParentLayerId();

                    if (!ON_UuidIsNil(temp_parent_id))
                    {
                        // Find parent layer in temp doc
                        int temp_parent_idx = -1;
                        for (int li = 0; li < temp_doc->m_layer_table.LayerCount(); ++li)
                        {
                            if (temp_doc->m_layer_table[li].Id() == temp_parent_id)
                            {
                                temp_parent_idx = li;
                                break;
                            }
                        }
                        
                        if (temp_parent_idx >= 0)
                        {
                            const CRhinoLayer& parent_layer = temp_doc->m_layer_table[temp_parent_idx];
                            
                            // Build parent full path
                            ON_wString parent_name = parent_layer.Name();
                            ON_wString parent_fullpath = parent_name;
                            ON_UUID grandparent_id = parent_layer.ParentLayerId();
                            while (!ON_UuidIsNil(grandparent_id))
                            {
                                int gp_idx = -1;
                                for (int li = 0; li < temp_doc->m_layer_table.LayerCount(); ++li)
                                {
                                    if (temp_doc->m_layer_table[li].Id() == grandparent_id)
                                    {
                                        gp_idx = li;
                                        break;
                                    }
                                }
                                if (gp_idx < 0) break;
                                const CRhinoLayer& gp_layer = temp_doc->m_layer_table[gp_idx];
                                parent_fullpath = gp_layer.Name() + L"::" + parent_fullpath;
                                grandparent_id = gp_layer.ParentLayerId();
                            }

                            // Find or create parent in main doc
                            int main_parent_idx = doc->m_layer_table.FindLayerFromName(
                                static_cast<const wchar_t*>(parent_fullpath),
                                true, true, -1, -1
                            );
                            
                            if (main_parent_idx < 0)
                            {
                                // Create parent layer
                                ON_Layer new_parent;
                                new_parent.SetName(parent_name);
                                new_parent.SetColor(parent_layer.Color());
                                main_parent_idx = doc->m_layer_table.AddLayer(new_parent);
                            }

                            if (main_parent_idx >= 0)
                                main_parent_id = doc->m_layer_table[main_parent_idx].Id();
                        }
                    }

                    // Now create the child layer
                    ON_Layer new_layer;
                    new_layer.SetName(src_layer_name);
                    new_layer.SetColor(src_layer.Color());
                    if (!ON_UuidIsNil(main_parent_id))
                        new_layer.SetParentId(main_parent_id);
                    
                    main_layer_index = doc->m_layer_table.AddLayer(new_layer);
                }
                
                attr.m_layer_index = main_layer_index;

                const ON_Geometry* geom = obj->Geometry();
                if (geom) {
                    std::unique_ptr<ON_Geometry> moved_geom(geom->Duplicate());
                    if (moved_geom)
                        moved_geom->Transform(move_xform);
                    if (const ON_Brep* brep = ON_Brep::Cast(moved_geom.get())) 
                    {
                        // Add brep
                        doc->AddBrepObject(*brep, &attr);
                        ++copied_count;

                        // After placing a Brep, extract border (naked edges) to PRE::CrvContour layer
                        int borders_added = AddBrepBorderCurvesToContourLayer(doc, brep);
                        if (borders_added > 0)
                        {
                          RhinoApp().Print(L" ➕ Added %d border curves to PRE::CrvContour.\n", borders_added);
                        }
                    } else if (const ON_Curve* curve = ON_Curve::Cast(moved_geom.get())) 
                    {
                        doc->AddCurveObject(*curve, &attr);
                        ++copied_count;
                    } else if (const ON_Mesh* mesh = ON_Mesh::Cast(moved_geom.get())) 
                    {
                        doc->AddMeshObject(*mesh, &attr);
                        ++copied_count;
                    }
                    else if (const ON_Extrusion* extrusion = ON_Extrusion::Cast(moved_geom.get()))
                    {
                        doc->AddExtrusionObject(*extrusion, &attr);
                        ++copied_count;
                    }
                    else if (const ON_Surface* surface = ON_Surface::Cast(moved_geom.get()))
                    {
                        doc->AddSurfaceObject(*surface, &attr);
                        ++copied_count;
                    }
                    else if (const ON_Leader* leader = ON_Leader::Cast(moved_geom.get()))
                    {
                        // Get the style id from the ON_Leader object
                        ON_UUID style_id = leader->DimensionStyleId();
                        int dimstyle_index = temp_doc->m_dimstyle_table.FindDimStyleFromId(style_id, true, true, -1);
                        if (dimstyle_index >= 0)
                        {
                            const CRhinoDimStyle& src_dimstyle = temp_doc->m_dimstyle_table[dimstyle_index];
                            ON_wString style_name = src_dimstyle.Name();
                            int style_index = doc->m_dimstyle_table.FindDimStyleFromName(static_cast<const wchar_t*>(style_name), true, -1);
                            if (style_index < 0)
                            {
                                // Add the dimstyle if it doesn't exist
                                ON_DimStyle style = temp_doc->m_dimstyle_table[dimstyle_index];
                                doc->m_dimstyle_table.AddDimStyle(style, false);
                            }
                        }
                        CRhinoLeader* leader_obj = new CRhinoLeader();
                        leader_obj->SetLeader(*leader);
                        leader_obj->ModifyAttributes(attr, true);
                        doc->AddObject(leader_obj);
                        ++copied_count;
                    }
                    else if (const ON_Text* text = ON_Text::Cast(moved_geom.get()))
                    {
                        // Ensure the dimstyle used by the text exists in the destination doc
                        {
                          ON_UUID style_id = text->DimensionStyleId();
                          int src_dimstyle_index = temp_doc->m_dimstyle_table.FindDimStyleFromId(style_id, true, true, -1);
                          if (src_dimstyle_index >= 0)
                          {
                            const CRhinoDimStyle& src_dimstyle = temp_doc->m_dimstyle_table[src_dimstyle_index];
                            ON_wString style_name = src_dimstyle.Name();
                            int dst_style_index = doc->m_dimstyle_table.FindDimStyleFromName(static_cast<const wchar_t*>(style_name), true, -1);
                            if (dst_style_index < 0)
                            {
                              ON_DimStyle style_copy = temp_doc->m_dimstyle_table[src_dimstyle_index];
                              doc->m_dimstyle_table.AddDimStyle(style_copy, false);
                            }
                          }
                        }

                        // 1) Add the text entity on its original destination layer
                        {
                          ON_Text* newText = new ON_Text(*text);
                          CRhinoText* text_obj = new CRhinoText();
                          text_obj->SetTextObject(newText);
                          text_obj->ModifyAttributes(attr, true);
                          doc->AddObject(text_obj);
                          ++copied_count;
                        }

                        // 2) Duplicate the text entity onto PRE::TXTasCRV layer
                        int txt_layer_index = EnsureTxtAsCrvLayer(doc);
                        if (txt_layer_index < 0)
                        {
                          RhinoApp().Print(L"⚠️ Could not ensure PRE::TXTasCRV layer. Skipping text duplication.\n");
                        }
                        else
                        {
                          CRhinoObjectAttributes dup_attr = attr;
                          dup_attr.m_layer_index = txt_layer_index;

                          ON_Text* dupText = new ON_Text(*text);
                          CRhinoText* dup_text_obj = new CRhinoText();
                          dup_text_obj->SetTextObject(dupText);
                          dup_text_obj->ModifyAttributes(dup_attr, true);
                          doc->AddObject(dup_text_obj);
                          ++copied_count;
                        }
                    }
                    else
                    {
                        RhinoApp().Print(L"⚠️ Used AddObject for geometry type: %S\n", typeid(*geom).name());
                    }
                }
            }
        }

        if (copied_count > 0) {
            merged_files++;
            RhinoApp().Print(L"✅ Merged %d objects from target layers in file: %s\n", copied_count, file_path_str.c_str());
        } else {
            RhinoApp().Print(L"⚠️ No objects found in target layers in file: %s\n", file_path_str.c_str());
        }

        CRhinoDoc::CloseDocument(doc_sn);
        file_index++;
    }

    // After processing all files, select and explode everything on PRE::TXTasCRV layer
    {
      int txt_layer_index = EnsureTxtAsCrvLayer(doc);
      if (txt_layer_index >= 0)
      {
        // Convert any CRhinoText objects on PRE::TXTasCRV into glyph curves and delete the text objects
        ON_SimpleArray<ON_UUID> to_delete;
        int exploded_total = 0;

        CRhinoObjectIterator it_doc(
          doc->RuntimeSerialNumber(),
          CRhinoObjectIterator::undeleted_objects,
          CRhinoObjectIterator::active_and_reference_objects);

        for (CRhinoObject* o = it_doc.First(); o != nullptr; o = it_doc.Next())
        {
          if (o->Attributes().m_layer_index != txt_layer_index)
            continue;

          const CRhinoText* pTextObj = CRhinoText::Cast(o);
          if (!pTextObj)
            continue;

          // Effective style for this annotation
          const ON_DimStyle& eff_style = pTextObj->GetEffectiveDimensionStyle(doc);

          // Underlying ON_Text
          const ON_Text* on_text = pTextObj->TextObject(&eff_style);
          if (!on_text)
            continue;

          // Compute text transform to model space
          ON_Xform text_xform = ON_Xform::IdentityTransformation;
          on_text->GetTextXform((const ON_Viewport*)nullptr, &eff_style, 1.0, text_xform);

          // Get glyph contours and add curves on the same layer
          const ON_TextContent* content = on_text->Text();
          int added_curves = 0;
          if (content)
          {
            const ON_Font& def_font = content->DefaultFont();
            ON_ClassArray< ON_ClassArray< ON_SimpleArray< ON_Curve* > > > contours;
            if (content->GetGlyphContours(&def_font, false, text_xform, contours))
            {
              CRhinoObjectAttributes attr_crv;
              attr_crv.m_layer_index = txt_layer_index;

              for (int i_run = 0; i_run < contours.Count(); ++i_run)
              {
                auto& run_contours = contours[i_run];
                for (int j = 0; j < run_contours.Count(); ++j)
                {
                  auto& glyph_curves = run_contours[j];
                  for (int k = 0; k < glyph_curves.Count(); ++k)
                  {
                    ON_Curve* c = glyph_curves[k];
                    if (c)
                    {
                      if (doc->AddCurveObject(*c, &attr_crv))
                        ++added_curves;
                      delete c;
                      glyph_curves[k] = nullptr;
                    }
                  }
                }
              }
            }
          }

          if (added_curves > 0)
          {
            exploded_total += added_curves;
            to_delete.Append(o->Attributes().m_uuid);
          }
        }

        // Delete original texts now that they are exploded to curves
        for (int i = 0; i < to_delete.Count(); ++i)
        {
          CRhinoObjRef objref(context.m_doc.RuntimeSerialNumber(), to_delete[i]);
          doc->DeleteObject(objref);
        }

        if (exploded_total > 0)
          RhinoApp().Print(L" ✳️ Exploded %d glyph curves on PRE::TXTasCRV.\n", exploded_total);
      }
    }

    context.m_doc.Redraw();
    if (merged_files == 0)
        RhinoApp().Print(L"⚠️ No geometry merged.\n");
    else
        RhinoApp().Print(L"✅ Done! Merged geometry from %d files.\n", merged_files);

    return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_AppendGeometry command
//
//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
