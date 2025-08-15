// cmdANM_CreateLinearDim.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_CreateLinearDim command
//

#pragma region ANM_CreateLinearDim command

class CCommandANM_CreateLinearDim : public CRhinoCommand
{
public:
	CCommandANM_CreateLinearDim() = default;
	UUID CommandUUID() override
	{
		// {02b652c6-9b78-4370-8aa9-c16e94f30fad}
		static const GUID ANM_CreateLinearDimCommand_UUID =
		{0x02b652c6,0x9b78,0x4370,{0x8a,0xa9,0xc1,0x6e,0x94,0xf3,0x0f,0xad}};
		return ANM_CreateLinearDimCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_CreateLinearDim"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_CreateLinearDim object
static class CCommandANM_CreateLinearDim theANM_CreateLinearDimCommand;

CRhinoCommand::result CCommandANM_CreateLinearDim::RunCommand(const CRhinoCommandContext& context)
{
	ON_SimpleArray<ON_Line> lines;
	SelectLines(lines, L"Select lines to create linear dimensions");

	if(lines.Count() < 1)
	{
		RhinoApp().Print(L"Please select lines.\n");
		return CRhinoCommand::failure;
	}

	// After selecting the lines, we prompt the user to select a point
	ON_3dPoint dimPt;
	SelectPoint(dimPt, L"Select points to create linear dimensions");
	if(dimPt.IsValid() == false)
	{
		RhinoApp().Print(L"Please select a valid point.\n");
		return CRhinoCommand::failure;
	}

	CRhinoDimLinear* dimObj = 0;
	ON_Plane plane = ON_xy_plane;

	for (int i = 0; i < lines.Count(); i++)
	{
		ON_3dPoint origin = lines[i].from;
		ON_3dPoint offset = lines[i].to;

	}



	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_CreateLinearDim command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
