// cmdCurveCreator.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN CurveCreator command
//

#pragma region CurveCreator command

class CCommandCurveCreator : public CRhinoCommand
{
public:
	CCommandCurveCreator() = default;
	UUID CommandUUID() override
	{
		// {99710a07-fdea-4fd0-83ea-63680ef6392b}
		static const GUID CurveCreatorCommand_UUID =
		{0x99710a07,0xfdea,0x4fd0,{0x83,0xea,0x63,0x68,0x0e,0xf6,0x39,0x2b}};
		return CurveCreatorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"CurveCreator"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandCurveCreator object
static class CCommandCurveCreator theCurveCreatorCommand;

CRhinoCommand::result CCommandCurveCreator::RunCommand(const CRhinoCommandContext& context)
{
	ON_3dPointArray points;
	SelectPoints(points, L"Select points to create a curve");
	if (points.Count() < 1)

	RhinoApp().Print(L"Creating curve from %d points...\n", points.Count());

	return CRhinoCommand::success;
}

#pragma endregion

//
// END CurveCreator command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
