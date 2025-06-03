// cmdGetCRhinoObject.cpp : command file
//

#include "stdafx.h"
#include "GetCRhinoObjectPlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN GetCRhinoObject command
//

#pragma region GetCRhinoObject command

// Do NOT put the definition of class CCommandGetCRhinoObject in a header
// file. There is only ONE instance of a CCommandGetCRhinoObject class
// and that instance is the static theGetCRhinoObjectCommand that appears
// immediately below the class definition.

class CCommandGetCRhinoObject : public CRhinoCommand
{
public:
  // The one and only instance of CCommandGetCRhinoObject is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandGetCRhinoObject::CCommandGetCRhinoObject()
  // is called exactly once when static theGetCRhinoObjectCommand is created.
  CCommandGetCRhinoObject() = default;

  // CCommandGetCRhinoObject::~CCommandGetCRhinoObject()
  // is called exactly once when static theGetCRhinoObjectCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandGetCRhinoObject() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {B4A39D6F-879E-4678-BA27-AA76BE76C5F9}
    static const GUID GetCRhinoObjectCommand_UUID = 
    {0xb4a39d6f,0x879e,0x4678,{0xba,0x27,0xaa,0x76,0xbe,0x76,0xc5,0xf9}};
    return GetCRhinoObjectCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"GetCRhinoObject"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandGetCRhinoObject object
// Do NOT create any other instance of a CCommandGetCRhinoObject class.
static class CCommandGetCRhinoObject theGetCRhinoObjectCommand;

CRhinoCommand::result CCommandGetCRhinoObject::RunCommand(const CRhinoCommandContext& context)
{
    CRhinoGetObject go;
	go.EnablePreSelect(false);

    go.SetGeometryFilter(CRhinoGetObject::point_object |
                         CRhinoGetObject::curve_object);

	go.SetCommandPrompt(L"Select point or curve object");
    CRhinoGetObject::result res = go.GetObjects(1, 1); // Get exactly one object

    if (res == CRhinoGetObject::result::no_result || 
        res == CRhinoGetObject::result::cancel || 
        res == CRhinoGetObject::result::nothing)
    {
        RhinoApp().Print(L"There was no element selected");
    }
    else
    {
        const CRhinoObjRef& obj_rhino = go.Object(0);
		const CRhinoObject* obj = obj_rhino.Object();

        if (obj != nullptr)
        {
            RhinoApp().Print(L"The name of the selected object is %s", obj->Attributes().m_name);
        }
    }


  return CRhinoCommand::success;
}

#pragma endregion

//
// END GetCRhinoObject command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
