// cmdBrepSelector.cpp : command file
//

#include "stdafx.h"
#include "BrepSelectorPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN BrepSelector command
//

#pragma region BrepSelector command

// Do NOT put the definition of class CCommandBrepSelector in a header
// file. There is only ONE instance of a CCommandBrepSelector class
// and that instance is the static theBrepSelectorCommand that appears
// immediately below the class definition.

class CCommandBrepSelector : public CRhinoCommand
{
public:
  // The one and only instance of CCommandBrepSelector is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandBrepSelector::CCommandBrepSelector()
  // is called exactly once when static theBrepSelectorCommand is created.
  CCommandBrepSelector() = default;

  // CCommandBrepSelector::~CCommandBrepSelector()
  // is called exactly once when static theBrepSelectorCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandBrepSelector() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {FE691F87-0F9E-4458-9263-4A1C3D4E600A}
    static const GUID BrepSelectorCommand_UUID = 
    {0xfe691f87,0x0f9e,0x4458,{0x92,0x63,0x4a,0x1c,0x3d,0x4e,0x60,0x0a}};
    return BrepSelectorCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"BrepSelector"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandBrepSelector object
// Do NOT create any other instance of a CCommandBrepSelector class.
static class CCommandBrepSelector theBrepSelectorCommand;

CRhinoCommand::result CCommandBrepSelector::RunCommand(const CRhinoCommandContext& context)
{
	CRhinoGetObject go;
	go.EnablePreSelect(false);
	go.SetCommandPrompt(L"Select a surface or a polysurface");
	go.SetGeometryFilter(CRhinoGetObject::surface_object | CRhinoGetObject::polysrf_object);

	CRhinoGetObject::result res = go.GetObjects(1, 0);

	int count = go.ObjectCount();
	int polysurfacesCount = 0;

	ON_SimpleArray<ON_Brep*> arrBreps;
	//ON_SimpleArray<ON_BrepFace*> newFaces;

	if (res == CRhinoGetObject::object) 
	{
		for (int i = 0; i < count; i++)
		{
			CRhinoObjRef &obj_ref = go.Object(i);

			ON_Brep* brep = obj_ref.Brep()->BrepForm();
			//const ON_Brep* brep = obj_ref.Brep();
			//const ON_BrepFace* srf = brep->m_F.At(0);
			//newFaces.Append(srf->Duplicate());

			if (brep) {
				arrBreps.Append(brep);
			}

			if (brep->m_F.Count() > 1) polysurfacesCount++;
		}

		RhinoApp().Print(L"Number of Breps selected: %d\n", arrBreps.Count());
		RhinoApp().Print(L"Number of polysurfaces selected: %d\n", polysurfacesCount);

		return CRhinoCommand::success;
	}
	else
	{
		return CRhinoCommand::cancel;
	}
}

#pragma endregion

//
// END BrepSelector command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
