// cmdANM_MeshCreator.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_MeshCreator command
//

#pragma region ANM_MeshCreator command

class CCommandANM_MeshCreator : public CRhinoCommand
{
public:
	CCommandANM_MeshCreator() = default;
	UUID CommandUUID() override
	{
		// {cd71aff6-869c-420f-bdef-f331a01ee654}
		static const GUID ANM_MeshCreatorCommand_UUID =
		{0xcd71aff6,0x869c,0x420f,{0xbd,0xef,0xf3,0x31,0xa0,0x1e,0xe6,0x54}};
		return ANM_MeshCreatorCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_MeshCreator"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_MeshCreator object
static class CCommandANM_MeshCreator theANM_MeshCreatorCommand;

CRhinoCommand::result CCommandANM_MeshCreator::RunCommand(const CRhinoCommandContext& context)
{
	ON_3dPointArray points;

	SelectPoints(points, L"Select points to create mesh in the proper order.");

	int vertexCount = 9;
	int faceCount = 8;
	bool hasVNormals = false;
	bool hasTCoor = false;
	ON_Mesh mesh(vertexCount, faceCount, hasVNormals, hasTCoor);

	for (int i = 0; i < points.Count(); i++)
	{
		mesh.SetVertex(i, points[i]);
	}

	mesh.SetTriangle(0, 0, 1, 2);
	mesh.SetTriangle(1, 0, 2, 3);
	mesh.SetTriangle(2, 0, 3, 4);
	mesh.SetTriangle(3, 0, 4, 5);
	mesh.SetTriangle(4, 0, 5, 6);
	mesh.SetTriangle(5, 0, 6, 7);
	mesh.SetTriangle(6, 0, 7, 8);
	mesh.SetTriangle(7, 0, 8, 1);

	mesh.ComputeVertexNormals();

	if (mesh.IsValid())
	{
		context.m_doc.AddMeshObject(mesh);
		return CRhinoCommand::success;
	}
	else 
	{
		RhinoApp().Print(L"Mesh creation failed. Please check the input points.\n");
		return CRhinoCommand::failure;
	}

}

#pragma endregion

//
// END ANM_MeshCreator command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
