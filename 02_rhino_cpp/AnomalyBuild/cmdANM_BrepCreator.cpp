// cmdANM_BrepCreator.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_BrepCreator command
//

#pragma region ANM_BrepCreator command

class CCommandANM_BrepCreator : public CRhinoCommand
{
public:
	CCommandANM_BrepCreator() = default;
	UUID CommandUUID() override
	{
		// {65725ef8-0840-435a-913b-ffe0134a8b7b}
		static const GUID ANM_BrepCreatorCommand_UUID =
		{0x65725ef8,0x0840,0x435a,{0x91,0x3b,0xff,0xe0,0x13,0x4a,0x8b,0x7b}};
		return ANM_BrepCreatorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_BrepCreator"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_BrepCreator object
static class CCommandANM_BrepCreator theANM_BrepCreatorCommand;

CRhinoCommand::result CCommandANM_BrepCreator::RunCommand(const CRhinoCommandContext& context)
{
	ON_SimpleArray<ON_Curve*> arrCurves;
	SelectCurves(arrCurves, L"Select curves to create a brep from");
	if (arrCurves.Count() < 1)
	{
		RhinoApp().Print(L"Please select at least a curve.\n");
		return CRhinoCommand::failure;
	}
	
	//ON_Brep* brep = CreateBrepFromPlanarCurves(arrCurves);
	ON_Brep* brep = CreateBrepFromEdgeCurves(arrCurves);

	if (brep) context.m_doc.AddBrepObject(*brep);
	else
	{
		RhinoApp().Print(L"Failed to create brep from curves.\n");
		return CRhinoCommand::failure;
	}

	if (brep)
	{
		delete brep;
		brep = 0;
	}

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_BrepCreator command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
