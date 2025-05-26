// cmdGetPoints.cpp : command file
//

#include "stdafx.h"
#include "GetPointsPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN GetPoints command
//

#pragma region GetPoints command

// Do NOT put the definition of class CCommandGetPoints in a header
// file. There is only ONE instance of a CCommandGetPoints class
// and that instance is the static theGetPointsCommand that appears
// immediately below the class definition.

class CCommandGetPoints : public CRhinoCommand
{
public:
  // The one and only instance of CCommandGetPoints is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandGetPoints::CCommandGetPoints()
  // is called exactly once when static theGetPointsCommand is created.
  CCommandGetPoints() = default;

  // CCommandGetPoints::~CCommandGetPoints()
  // is called exactly once when static theGetPointsCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandGetPoints() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {C7D95FB4-B07B-47BE-9CC4-7DEBDFF34DAE}
    static const GUID GetPointsCommand_UUID = 
    {0xc7d95fb4,0xb07b,0x47be,{0x9c,0xc4,0x7d,0xeb,0xdf,0xf3,0x4d,0xae}};
    return GetPointsCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"GetPoints"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandGetPoints object
// Do NOT create any other instance of a CCommandGetPoints class.
static class CCommandGetPoints theGetPointsCommand;

CRhinoCommand::result CCommandGetPoints::RunCommand(const CRhinoCommandContext& context)
{
    CRhinoGetPoint gp;
    CString message = L"Pick a point any point";
    gp.SetCommandPrompt(message);

    gp.GetPoint();

    ON_3dPoint pt = gp.Point();

    if (gp.GetPoint() == CRhinoGet::no_result)
        RhinoApp().Print(L"Nothing selected.");

    RhinoApp().Print(L"%f %f %f \n", pt.x, pt.y, pt.z);

    return CRhinoCommand::success;
}

#pragma endregion

//
// END GetPoints command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
