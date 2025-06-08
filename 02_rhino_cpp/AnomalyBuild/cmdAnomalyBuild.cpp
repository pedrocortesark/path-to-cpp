//// cmdAnomalyBuild.cpp : command file
////
//
#include "stdafx.h"
//#include "AnomalyBuildPlugIn.h"
//#include "AnomalyFunctions.h"
//
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
////
//// BEGIN AnomalyBuild command
////
//
//#pragma region AnomalyBuild command
//
//// Do NOT put the definition of class CCommandAnomalyBuild in a header
//// file. There is only ONE instance of a CCommandAnomalyBuild class
//// and that instance is the static theAnomalyBuildCommand that appears
//// immediately below the class definition.
//
//class CCommandAnomalyBuild : public CRhinoCommand
//{
//public:
//	// The one and only instance of CCommandAnomalyBuild is created below.
//	// No copy constructor or operator= is required.
//	// Values of member variables persist for the duration of the application.
//
//	// CCommandAnomalyBuild::CCommandAnomalyBuild()
//	// is called exactly once when static theAnomalyBuildCommand is created.
//	CCommandAnomalyBuild() = default;
//
//	// CCommandAnomalyBuild::~CCommandAnomalyBuild()
//	// is called exactly once when static theAnomalyBuildCommand is destroyed.
//	// The destructor should not make any calls to the Rhino SDK. 
//	// If your command has persistent settings, then override 
//	// CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
//	~CCommandAnomalyBuild() = default;
//
//	// Returns a unique UUID for this command.
//	// If you try to use an id that is already being used, then
//	// your command will not work. Use GUIDGEN.EXE to make unique UUID.
//	UUID CommandUUID() override
//	{
//		// {494B484F-6241-49ED-82E5-49FF74C21B46}
//		static const GUID AnomalyBuildCommand_UUID =
//		{ 0x494b484f,0x6241,0x49ed,{0x82,0xe5,0x49,0xff,0x74,0xc2,0x1b,0x46} };
//		return AnomalyBuildCommand_UUID;
//	}
//
//	// Returns the English command name.
//	// If you want to provide a localized command name, then override 
//	// CRhinoCommand::LocalCommandName.
//	const wchar_t* EnglishCommandName() override { return L"AnomalyBuild"; }
//
//	// Rhino calls RunCommand to run the command.
//	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
//};
//
//// The one and only CCommandAnomalyBuild object
//// Do NOT create any other instance of a CCommandAnomalyBuild class.
//static class CCommandAnomalyBuild theAnomalyBuildCommand;
//
//CRhinoCommand::result CCommandAnomalyBuild::RunCommand(const CRhinoCommandContext& context)
//{
//	CRhinoGetObject go;
//	go.EnablePreSelect(false);
//	go.SetCommandPrompt(L"Select a line to build an anomaly point on");
//	go.SetGeometryFilter(CRhinoGetObject::curve_object);
//
//	CRhinoGetObject::result res = go.GetObjects(1, 1);
//	if (res != CRhinoGetObject::object) {
//		RhinoApp().Print(L"No curve element found.");
//		return CRhinoCommand::cancel; // User cancelled the command
//	}
//
//	const CRhinoObjRef& obj_ref = go.Object(0);
//	const CRhinoCurveObject* curve_obj = CRhinoCurveObject::Cast(obj_ref.Object());
//	const ON_Curve* c = curve_obj->Curve();
//	ON_Line line = ON_Line(c->PointAtStart(), c->PointAtEnd());
//
//	ON_3dPoint pt = ANM_DrawPoint(line, true);
//	context.m_doc.AddPointObject(pt); // Add the point to the document
//	context.m_doc.Redraw();
//
//	return CRhinoCommand::success; // Return success or failure
//}
//
//#pragma endregion
//
////
//// END AnomalyBuild command
////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////