// cmdBrepCreateor.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN BrepCreateor command
//

#pragma region BrepCreateor command

class CCommandBrepCreateor : public CRhinoCommand
{
public:
	CCommandBrepCreateor() = default;
	UUID CommandUUID() override
	{
		// {4cf847f3-c136-4c50-b55b-7faf80eb42ec}
		static const GUID BrepCreateorCommand_UUID =
		{0x4cf847f3,0xc136,0x4c50,{0xb5,0x5b,0x7f,0xaf,0x80,0xeb,0x42,0xec}};
		return BrepCreateorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"BrepCreateor"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandBrepCreateor object
static class CCommandBrepCreateor theBrepCreateorCommand;

CRhinoCommand::result CCommandBrepCreateor::RunCommand(const CRhinoCommandContext& context)
{
	ON_SimpleArray<ON_Curve*> arrCurves;
	SelectCurves(arrCurves, L"Select curves to create a brep from");
	if (arrCurves.Count() < 1)
	{
		RhinoApp().Print(L"Please select at least a curve.\n");
		return CRhinoCommand::failure;
	}
	ON_Brep* brep = CreateBrepFromPlanarCurves(arrCurves);
	if(brep) context.m_doc.AddBrepObject(*brep);
	else
	{
		RhinoApp().Print(L"Failed to create brep from curves.\n");
		return CRhinoCommand::failure;
	}

	return CRhinoCommand::success;
}

#pragma endregion

//
// END BrepCreateor command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
