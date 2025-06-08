// cmdANM_CircleCreator.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_CircleCreator command
//

#pragma region ANM_CircleCreator command

class CCommandANM_CircleCreator : public CRhinoCommand
{
public:
	CCommandANM_CircleCreator() = default;
	UUID CommandUUID() override
	{
		// {be32e670-91fa-431e-a477-620465161c51}
		static const GUID ANM_CircleCreatorCommand_UUID =
		{0xbe32e670,0x91fa,0x431e,{0xa4,0x77,0x62,0x04,0x65,0x16,0x1c,0x51}};
		return ANM_CircleCreatorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_CircleCreator"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_CircleCreator object
static class CCommandANM_CircleCreator theANM_CircleCreatorCommand;

CRhinoCommand::result CCommandANM_CircleCreator::RunCommand(const CRhinoCommandContext& context)
{
	CRhinoDoc* doc = ::RhinoApp().ActiveDoc();

	ON_3dPointArray points;
	SelectPoints(points, L"Select points to create circles");

	CreateCircle(points, doc);

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_CircleCreator command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
