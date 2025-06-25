// cmdANM_MeshBrep.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_MeshBrep command
//

#pragma region ANM_MeshBrep command

class CCommandANM_MeshBrep : public CRhinoCommand
{
public:
	CCommandANM_MeshBrep() = default;
	UUID CommandUUID() override
	{
		// {0fbb58c3-d4bf-42c0-99ad-41e6f0fd7561}
		static const GUID ANM_MeshBrepCommand_UUID =
		{0x0fbb58c3,0xd4bf,0x42c0,{0x99,0xad,0x41,0xe6,0xf0,0xfd,0x75,0x61}};
		return ANM_MeshBrepCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_MeshBrep"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_MeshBrep object
static class CCommandANM_MeshBrep theANM_MeshBrepCommand;

CRhinoCommand::result CCommandANM_MeshBrep::RunCommand(const CRhinoCommandContext& context)
{
	bool qualityMesh = false;

	ON_MeshParameters mp;

	if (qualityMesh)
		mp = ON_MeshParameters::QualityRenderMesh;
	else
		mp = ON_MeshParameters::FastRenderMesh;

	ON_Brep* brep;
	SelectBrep(brep, L"Select a simple brep");

	if (!brep)
	{
		RhinoApp().Print(L"Sorry! Nothing selected.\n");
		return CRhinoCommand::cancel;
	}

	ON_SimpleArray<ON_Mesh*> meshes(brep->m_F.Count());
	int meshCount = brep->CreateMesh(mp, meshes);

	if(meshCount == brep->m_F.Count())
	{
		for (int i = 0; i < meshCount; i++)
		{
			context.m_doc.AddMeshObject(*meshes[i]);
		}
	}

	context.m_doc.Redraw();

	return CRhinoCommand::success;
}

#pragma endregion

//
// END ANM_MeshBrep command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
