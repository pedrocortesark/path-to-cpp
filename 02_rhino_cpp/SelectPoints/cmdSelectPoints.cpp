// cmdSelectPoints.cpp : command file
//

#include "stdafx.h"
#include "SelectPointsPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN SelectPoints command
//

#pragma region SelectPoints command

// Do NOT put the definition of class CCommandSelectPoints in a header
// file. There is only ONE instance of a CCommandSelectPoints class
// and that instance is the static theSelectPointsCommand that appears
// immediately below the class definition.

class CCommandSelectPoints : public CRhinoCommand
{
public:
  // The one and only instance of CCommandSelectPoints is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandSelectPoints::CCommandSelectPoints()
  // is called exactly once when static theSelectPointsCommand is created.
  CCommandSelectPoints() = default;

  // CCommandSelectPoints::~CCommandSelectPoints()
  // is called exactly once when static theSelectPointsCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandSelectPoints() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {30ED5E81-7394-4CA0-B140-E22744581964}
    static const GUID SelectPointsCommand_UUID = 
    {0x30ed5e81,0x7394,0x4ca0,{0xb1,0x40,0xe2,0x27,0x44,0x58,0x19,0x64}};
    return SelectPointsCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"SelectPoints"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandSelectPoints object
// Do NOT create any other instance of a CCommandSelectPoints class.
static class CCommandSelectPoints theSelectPointsCommand;

CRhinoCommand::result CCommandSelectPoints::RunCommand(const CRhinoCommandContext& context)
{
	CRhinoGetObject go;
	go.EnablePreSelect(false);
	go.SetCommandPrompt(L"Select multiple points");

    go.SetGeometryFilter(CRhinoGetObject::point_object);

	CRhinoGet::result res = go.GetObjects(1, 0);
    int count = go.ObjectCount();

    ON_3dPointArray points;
    if (res == CRhinoGet::object) 
    {
        for (int i = 0; i < count; i++)
        {
			const CRhinoObjRef& obj_ref = go.Object(i);
			const ON_Point* point = obj_ref.Point();

            ON_3dPoint pt(point->point.x, point->point.y, point->point.z);
            
            points.Append(pt);
        }

    }

	RhinoApp().Print(L"Selected %d points.\n", points.Count());
    return CRhinoCommand::success;
}

#pragma endregion

//
// END SelectPoints command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
