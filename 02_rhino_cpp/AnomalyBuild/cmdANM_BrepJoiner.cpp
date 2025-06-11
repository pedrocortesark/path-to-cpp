// cmdANM_BrepJoiner.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_BrepJoiner command
//

#pragma region ANM_BrepJoiner command

class CCommandANM_BrepJoiner : public CRhinoCommand
{
public:
	CCommandANM_BrepJoiner() = default;
	UUID CommandUUID() override
	{
		// {563be3d6-15a2-4434-9ee8-480fa6ec0df4}
		static const GUID ANM_BrepJoinerCommand_UUID =
		{0x563be3d6,0x15a2,0x4434,{0x9e,0xe8,0x48,0x0f,0xa6,0xec,0x0d,0xf4}};
		return ANM_BrepJoinerCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_BrepJoiner"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_BrepJoiner object
static class CCommandANM_BrepJoiner theANM_BrepJoinerCommand;

CRhinoCommand::result CCommandANM_BrepJoiner::RunCommand(const CRhinoCommandContext& context)
{
	CRhinoDoc* doc = ::RhinoApp().ActiveDoc();

	ON_SimpleArray<ON_Brep*> arrBreps;
	SelectBreps(arrBreps, L"Select Breps to join");

	if (arrBreps.Count() < 2)
	{
		RhinoApp().Print(L"Please select more than one brep.");
		return CRhinoCommand::failure;
	}

	ON_SimpleArray<ON_Brep*> outBreps = JoinBreps(doc, arrBreps, true);

	if(outBreps.Count() == 0)
	{
		RhinoApp().Print(L"Failed to join breps.\n");
		return CRhinoCommand::failure;
	}

	for (int i = 0; i < outBreps.Count(); i++)
	{
		doc->AddBrepObject(*outBreps[i]);
		delete outBreps[i];
		outBreps[i] = nullptr;
	}

	outBreps.Destroy();

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_BrepJoiner command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
