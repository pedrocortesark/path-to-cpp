// cmdANM_CurveCreator.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_CurveCreator command
//

#pragma region ANM_CurveCreator command

class CCommandANM_CurveCreator : public CRhinoCommand
{
public:
	CCommandANM_CurveCreator() = default;
	UUID CommandUUID() override
	{
		// {c54e62eb-96f3-4a53-b993-348ff03ee106}
		static const GUID ANM_CurveCreatorCommand_UUID =
		{0xc54e62eb,0x96f3,0x4a53,{0xb9,0x93,0x34,0x8f,0xf0,0x3e,0xe1,0x06}};
		return ANM_CurveCreatorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_CurveCreator"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_CurveCreator object
static class CCommandANM_CurveCreator theANM_CurveCreatorCommand;

CRhinoCommand::result CCommandANM_CurveCreator::RunCommand(const CRhinoCommandContext& context)
{
	CRhinoDoc* doc = ::RhinoApp().ActiveDoc();

	ON_3dPointArray points;
	SelectPoints(points, L"Select points to create a curve");
	if (points.Count() < 1) return CRhinoCommand::failure;

	RhinoApp().Print(L"Creating curve from %d points...\n", points.Count());
	CreateCurveFromPoints(points, 3, doc);

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_CurveCreator command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
