// cmdGuerreroRPG.cpp
//

#include "stdafx.h"


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN GuerreroRPG command
//

#pragma region GuerreroRPG command

class CCommandGuerreroRPG : public CRhinoCommand
{
public:
	CCommandGuerreroRPG() = default;
	UUID CommandUUID() override
	{
		// {1827ab67-9805-4a2a-94b3-8b7e5b1d254e}
		static const GUID GuerreroRPGCommand_UUID =
		{0x1827ab67,0x9805,0x4a2a,{0x94,0xb3,0x8b,0x7e,0x5b,0x1d,0x25,0x4e}};
		return GuerreroRPGCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"GuerreroRPG"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandGuerreroRPG object
static class CCommandGuerreroRPG theGuerreroRPGCommand;

CRhinoCommand::result CCommandGuerreroRPG::RunCommand(const CRhinoCommandContext& context)
{
	ON_wString str;
	str.Format( L"The \"%s\" command is under construction.\n", EnglishCommandName() );
	if (context.IsInteractive())
		RhinoMessageBox(str, EnglishCommandName(), MB_OK);
	else
		RhinoApp().Print(str);
	return CRhinoCommand::success;
}

#pragma endregion

//
// END GuerreroRPG command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
