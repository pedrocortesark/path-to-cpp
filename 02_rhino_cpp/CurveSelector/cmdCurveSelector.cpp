// cmdCurveSelector.cpp : command file
//

#include "stdafx.h"
#include "CurveSelectorPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN CurveSelector command
//

#pragma region CurveSelector command

// Do NOT put the definition of class CCommandCurveSelector in a header
// file. There is only ONE instance of a CCommandCurveSelector class
// and that instance is the static theCurveSelectorCommand that appears
// immediately below the class definition.

class CCommandCurveSelector : public CRhinoCommand
{
public:
  // The one and only instance of CCommandCurveSelector is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandCurveSelector::CCommandCurveSelector()
  // is called exactly once when static theCurveSelectorCommand is created.
  CCommandCurveSelector() = default;

  // CCommandCurveSelector::~CCommandCurveSelector()
  // is called exactly once when static theCurveSelectorCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandCurveSelector() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {3685A137-637D-402B-BE32-B9B90D03C79E}
    static const GUID CurveSelectorCommand_UUID = 
    {0x3685a137,0x637d,0x402b,{0xbe,0x32,0xb9,0xb9,0x0d,0x03,0xc7,0x9e}};
    return CurveSelectorCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"CurveSelector"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandCurveSelector object
// Do NOT create any other instance of a CCommandCurveSelector class.
static class CCommandCurveSelector theCurveSelectorCommand;

CRhinoCommand::result CCommandCurveSelector::RunCommand(const CRhinoCommandContext& context)
{
	CRhinoGetObject go;
	go.EnablePreSelect(false);
	go.SetCommandPrompt(L"Select curves to filter by length");
	go.SetGeometryFilter(CRhinoGetObject::curve_object);

	CRhinoGetObject::result res = go.GetObjects(1, 0);

	int count = go.ObjectCount();
	int polylines = 0;

	ON_SimpleArray<ON_Curve*> arrCrvs;
	ON_ClassArray<ON_Line> arrLines;

	if (res == CRhinoGetObject::object) {

		for (int i = 0; i < count; i++)
		{
			const CRhinoObjRef& obj_ref = go.Object(i);
			const CRhinoCurveObject* crv_obj = CRhinoCurveObject::Cast(obj_ref.Object());

			const ON_Curve* crv = crv_obj ? crv_obj->Curve() : nullptr;

			if (crv)
			{
				if (crv->IsPolyline()) polylines++;
				arrCrvs.Append(crv->Duplicate());

				ON_Line line(crv->PointAtStart(), crv->PointAtEnd());
				arrLines.Append(line);
			}
		}

		RhinoApp().Print(L"You selected: %d curves\n", arrCrvs.Count());
		RhinoApp().Print(L"Polylines: %d\n", polylines);
	}
	else {
		return CRhinoCommand::failure;
	}

	return CRhinoCommand::success;

}

#pragma endregion

//
// END CurveSelector command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
