// cmdMyRhinoCommand.cpp
//

#include "stdafx.h"
#include "AnomalyBuildApp.h"


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_HideAndSeek command
//

#pragma region ANM_HideAndSeek command

class CCommandMyRhinoCommand : public CRhinoCommand
{
public:
	CCommandMyRhinoCommand() = default;
	UUID CommandUUID() override
	{
		// {11b972f6-1b45-428a-b5c1-057b76d764d5}
		static const GUID MyRhinoCommandCommand_UUID =
		{0x11b972f6,0x1b45,0x428a,{0xb5,0xc1,0x05,0x7b,0x76,0xd7,0x64,0xd5}};
		return MyRhinoCommandCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_HideAndSeek"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandMyRhinoCommand object
static class CCommandMyRhinoCommand thecmdANM_HideAndSeekCommand;

CRhinoCommand::result CCommandMyRhinoCommand::RunCommand(const CRhinoCommandContext& context)
{
	ON_Line line0{ ON_3dPoint {0,0,0}, ON_3dPoint { 10,0,0 } };
	CRhinoObject* newLine = context.m_doc.AddCurveObject(line0);

	context.m_doc.Redraw();
	RhinoApp().Wait(10000);

	//context.m_doc.DeleteObject(newLine);
	context.m_doc.ReplaceObject(newLine, ON_LineCurve{ ON_3dPoint {10,10,10}, ON_3dPoint {15,15,15} });
	context.m_doc.Redraw();

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_HideAndSeek command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
