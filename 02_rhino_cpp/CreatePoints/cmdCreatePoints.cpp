// cmdCreatePoints.cpp : command file
//

#include "stdafx.h"
#include "CreatePointsPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN CreatePoints command
//

#pragma region CreatePoints command

// Do NOT put the definition of class CCommandCreatePoints in a header
// file. There is only ONE instance of a CCommandCreatePoints class
// and that instance is the static theCreatePointsCommand that appears
// immediately below the class definition.

class CCommandCreatePoints : public CRhinoCommand
{
public:
  // The one and only instance of CCommandCreatePoints is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandCreatePoints::CCommandCreatePoints()
  // is called exactly once when static theCreatePointsCommand is created.
  CCommandCreatePoints() = default;

  // CCommandCreatePoints::~CCommandCreatePoints()
  // is called exactly once when static theCreatePointsCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandCreatePoints() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {3F3EE341-FA5D-4BC4-B001-4BF4683113C1}
    static const GUID CreatePointsCommand_UUID = 
    {0x3f3ee341,0xfa5d,0x4bc4,{0xb0,0x01,0x4b,0xf4,0x68,0x31,0x13,0xc1}};
    return CreatePointsCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"CreatePoints"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandCreatePoints object
// Do NOT create any other instance of a CCommandCreatePoints class.
static class CCommandCreatePoints theCreatePointsCommand;

CRhinoCommand::result CCommandCreatePoints::RunCommand(const CRhinoCommandContext& context)
{
    ON_3dPoint pt1(0, 0, 0);
    ON_3dPoint pt2(10, 10, 10);

    context.m_doc.AddPointObject(pt1);
    context.m_doc.AddPointObject(pt2);
    context.m_doc.Redraw();

    return CRhinoCommand::success;
}

#pragma endregion

//
// END CreatePoints command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
