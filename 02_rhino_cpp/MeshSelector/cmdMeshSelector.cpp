// cmdMeshSelector.cpp : command file
//

#include "stdafx.h"
#include "MeshSelectorPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN MeshSelector command
//

#pragma region MeshSelector command

// Do NOT put the definition of class CCommandMeshSelector in a header
// file. There is only ONE instance of a CCommandMeshSelector class
// and that instance is the static theMeshSelectorCommand that appears
// immediately below the class definition.

class CCommandMeshSelector : public CRhinoCommand
{
public:
  // The one and only instance of CCommandMeshSelector is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandMeshSelector::CCommandMeshSelector()
  // is called exactly once when static theMeshSelectorCommand is created.
  CCommandMeshSelector() = default;

  // CCommandMeshSelector::~CCommandMeshSelector()
  // is called exactly once when static theMeshSelectorCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandMeshSelector() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {82841F27-3136-4AFA-BDB9-5134D7757FB2}
    static const GUID MeshSelectorCommand_UUID = 
    {0x82841f27,0x3136,0x4afa,{0xbd,0xb9,0x51,0x34,0xd7,0x75,0x7f,0xb2}};
    return MeshSelectorCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"MeshSelector"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandMeshSelector object
// Do NOT create any other instance of a CCommandMeshSelector class.
static class CCommandMeshSelector theMeshSelectorCommand;

CRhinoCommand::result CCommandMeshSelector::RunCommand(const CRhinoCommandContext& context)
{
    CRhinoGetObject go;
	go.EnablePreSelect(false);
	go.SetCommandPrompt(L"Select mesh objects");
	go.SetGeometryFilter(CRhinoGetObject::mesh_object);

	CRhinoGetObject::result res = go.GetObjects(1, 0);

	//ON_SimpleArray<ON_Mesh*> arrMeshes;
	ON_ClassArray<ON_Mesh> arrClassMeshes;
	int verticesCount = 0;
	int facesCount = 0;

	int count = go.ObjectCount();

	if (res == CRhinoGetObject::object)
	{
		for (int i = 0; i < count; i++)
		{
			CRhinoObjRef& obj_ref = go.Object(i);

			// Ref mesh - Option1 
			const CRhinoMeshObject* mesh_obj = CRhinoMeshObject::Cast(obj_ref.Object());
			if (!mesh_obj) continue;

			const ON_Mesh* mesh = mesh_obj->Mesh();
			ON_Mesh mesh_geo = *mesh;

			// Ref mesh - Option2
			const ON_Mesh* myMesh  = obj_ref.Mesh();
			if (!myMesh) continue;
			ON_Mesh mesh_geo2 = *myMesh;

			// Create a copy of the mesh
			//ON_Mesh* newMesh = obj_ref.Mesh()->Duplicate();

			if(mesh_geo.IsValid())
			{
				arrClassMeshes.Append(mesh_geo);
				verticesCount = mesh_geo.m_V.Count();
				facesCount = mesh_geo.m_F.Count();

				RhinoApp().Print(L"Mesh %d has %d vertices and %d vertices\n", i, verticesCount, facesCount);
			
				for (int j = 0; j < mesh_geo.m_N.Count(); j++)
				{
					context.m_doc.AddCurveObject(ON_Line(mesh_geo.m_V[j], mesh_geo.m_V[j] + mesh_geo.m_N[j]));
				}
			}
		}

		context.m_doc.Redraw();
		return CRhinoCommand::success;
	}
	else
	{
		return CRhinoCommand::failure;
	}

}

#pragma endregion

//
// END MeshSelector command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
