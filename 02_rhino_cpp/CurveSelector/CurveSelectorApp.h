// CurveSelector.h : main header file for the CurveSelector DLL.
//

#pragma once


#include "resource.h" // main symbols

// CCurveSelectorApp
// See CurveSelectorApp.cpp for the implementation of this class
//

class CCurveSelectorApp : public CWinApp
{
public:
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance construction belongs here. 
  // All other significant initialization should take place in
  // CCurveSelectorPlugIn::OnLoadPlugIn().
	CCurveSelectorApp() = default;

  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance initialization belongs here. 
  // All other significant initialization should take place in
  // CCurveSelectorPlugIn::OnLoadPlugIn().
	BOOL InitInstance() override;
  
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance clean up belongs here. 
  // All other significant cleanup should take place in either
  // CCurveSelectorPlugIn::OnSaveAllSettings() or
  // CCurveSelectorPlugIn::OnUnloadPlugIn().  
	int ExitInstance() override;
  
	DECLARE_MESSAGE_MAP()
};
