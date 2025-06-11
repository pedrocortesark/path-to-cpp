// cmdANM_BrepsCreator.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_BrepsCreator command
//

#pragma region ANM_BrepsCreator command

class CCommandANM_BrepsCreator : public CRhinoCommand
{
public:
	CCommandANM_BrepsCreator() = default;
	UUID CommandUUID() override
	{
		// {f3788043-9bd4-4721-99a6-f3bc083e0f86}
		static const GUID ANM_BrepsCreatorCommand_UUID =
		{0xf3788043,0x9bd4,0x4721,{0x99,0xa6,0xf3,0xbc,0x08,0x3e,0x0f,0x86}};
		return ANM_BrepsCreatorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_BrepsCreator"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_BrepsCreator object
static class CCommandANM_BrepsCreator theANM_BrepsCreatorCommand;

CRhinoCommand::result CCommandANM_BrepsCreator::RunCommand(const CRhinoCommandContext& context)
{
	CRhinoDoc* doc = ::RhinoApp().ActiveDoc();
	ON_SimpleArray<ON_Curve*> arrCurves;
	SelectCurves(arrCurves, L"Select curves to create several breps.");
	if (arrCurves.Count() < 1)
	{
		RhinoApp().Print(L"Please select at least a curve.\n");
		return CRhinoCommand::failure;
	}

	ON_SimpleArray<ON_Brep*> arrBreps = CreateSeveralBrepsFromPlanarCurves(arrCurves);
	if (arrBreps.Count() < 1)
	{
		RhinoApp().Print(L"Failed to create breps from curves.\n");
		return CRhinoCommand::failure;
	}

	for (int i = 0; i < arrBreps.Count(); i++)
	{
		doc->AddBrepObject(*arrBreps[i]);
		delete arrBreps[i];
		arrBreps[i] = 0;
	}

	arrBreps.Destroy();

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_BrepsCreator command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
