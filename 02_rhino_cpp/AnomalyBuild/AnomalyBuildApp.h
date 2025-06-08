// AnomalyBuild.h : main header file for the AnomalyBuild DLL.
//

#pragma once


#include "resource.h" // main symbols

// CAnomalyBuildApp
// See AnomalyBuildApp.cpp for the implementation of this class
//

class CAnomalyBuildApp : public CWinApp
{
public:
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance construction belongs here. 
  // All other significant initialization should take place in
  // CAnomalyBuildPlugIn::OnLoadPlugIn().
	CAnomalyBuildApp() = default;

  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance initialization belongs here. 
  // All other significant initialization should take place in
  // CAnomalyBuildPlugIn::OnLoadPlugIn().
	BOOL InitInstance() override;
  
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance clean up belongs here. 
  // All other significant cleanup should take place in either
  // CAnomalyBuildPlugIn::OnSaveAllSettings() or
  // CAnomalyBuildPlugIn::OnUnloadPlugIn().  
	int ExitInstance() override;
  
	DECLARE_MESSAGE_MAP()
};
