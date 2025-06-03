// GetCRhinoObject.h : main header file for the GetCRhinoObject DLL.
//

#pragma once


#include "resource.h" // main symbols

// CGetCRhinoObjectApp
// See GetCRhinoObjectApp.cpp for the implementation of this class
//

class CGetCRhinoObjectApp : public CWinApp
{
public:
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance construction belongs here. 
  // All other significant initialization should take place in
  // CGetCRhinoObjectPlugIn::OnLoadPlugIn().
	CGetCRhinoObjectApp() = default;

  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance initialization belongs here. 
  // All other significant initialization should take place in
  // CGetCRhinoObjectPlugIn::OnLoadPlugIn().
	BOOL InitInstance() override;
  
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance clean up belongs here. 
  // All other significant cleanup should take place in either
  // CGetCRhinoObjectPlugIn::OnSaveAllSettings() or
  // CGetCRhinoObjectPlugIn::OnUnloadPlugIn().  
	int ExitInstance() override;
  
	DECLARE_MESSAGE_MAP()
};
