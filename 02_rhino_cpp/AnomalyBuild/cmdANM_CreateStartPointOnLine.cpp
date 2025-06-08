// cmdANM_CreateStartPointOnLine.cpp
//

#include "stdafx.h"
#include "AnomalyFunctions.h"


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN ANM_CreateStartPointOnLine command
//

#pragma region ANM_CreateStartPointOnLine command

class CCommandANM_CreateStartPointOnLine : public CRhinoCommand
{
public:
	CCommandANM_CreateStartPointOnLine() = default;
	UUID CommandUUID() override
	{
		// {4dbbf2d1-72f3-4ec4-a9b7-65eb29e15f7e}
		static const GUID ANM_CreateStartPointOnLineCommand_UUID =
		{0x4dbbf2d1,0x72f3,0x4ec4,{0xa9,0xb7,0x65,0xeb,0x29,0xe1,0x5f,0x7e}};
		return ANM_CreateStartPointOnLineCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"ANM_CreateStartPointOnLine"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandANM_CreateStartPointOnLine object
static class CCommandANM_CreateStartPointOnLine theANM_CreateStartPointOnLineCommand;

CRhinoCommand::result CCommandANM_CreateStartPointOnLine::RunCommand(const CRhinoCommandContext& context)
{
	CRhinoGetObject go;
	go.EnablePreSelect(false);
	go.SetCommandPrompt(L"Select a line to build an anomaly point on");
	go.SetGeometryFilter(CRhinoGetObject::curve_object);

	CRhinoGetObject::result res = go.GetObjects(1, 1);
	if (res != CRhinoGetObject::object) {
		RhinoApp().Print(L"No curve element found.");
		return CRhinoCommand::cancel; // User cancelled the command
	}

	const CRhinoObjRef& obj_ref = go.Object(0);
	const CRhinoCurveObject* curve_obj = CRhinoCurveObject::Cast(obj_ref.Object());
	const ON_Curve* c = curve_obj->Curve();
	ON_Line line = ON_Line(c->PointAtStart(), c->PointAtEnd());

	ON_3dPoint pt = DrawPoint(line, true);
	context.m_doc.AddPointObject(pt); // Add the point to the document
	context.m_doc.Redraw();

	return CRhinoCommand::success; // Return success or failure
}

#pragma endregion

//
// END ANM_CreateStartPointOnLine command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
