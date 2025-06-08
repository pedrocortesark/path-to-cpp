// cmdANM_ArcCreator.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_ArcCreator command
//

#pragma region ANM_ArcCreator command

class CCommandANM_ArcCreator : public CRhinoCommand
{
public:
	CCommandANM_ArcCreator() = default;
	UUID CommandUUID() override
	{
		// {6f98d5a2-4517-4ae8-9d34-e31f12caa442}
		static const GUID ANM_ArcCreatorCommand_UUID =
		{0x6f98d5a2,0x4517,0x4ae8,{0x9d,0x34,0xe3,0x1f,0x12,0xca,0xa4,0x42}};
		return ANM_ArcCreatorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_ArcCreator"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_ArcCreator object
static class CCommandANM_ArcCreator theANM_ArcCreatorCommand;

CRhinoCommand::result CCommandANM_ArcCreator::RunCommand(const CRhinoCommandContext& context)
{
	CRhinoDoc* doc = ::RhinoApp().ActiveDoc();

	ON_3dPointArray points;
	SelectPoints(points, L"Select points to create circles");

	CreateArc(points, doc);

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_ArcCreator command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
