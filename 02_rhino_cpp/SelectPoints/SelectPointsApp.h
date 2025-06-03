// SelectPoints.h : main header file for the SelectPoints DLL.
//

#pragma once


#include "resource.h" // main symbols

// CSelectPointsApp
// See SelectPointsApp.cpp for the implementation of this class
//

class CSelectPointsApp : public CWinApp
{
public:
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance construction belongs here. 
  // All other significant initialization should take place in
  // CSelectPointsPlugIn::OnLoadPlugIn().
	CSelectPointsApp() = default;

  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance initialization belongs here. 
  // All other significant initialization should take place in
  // CSelectPointsPlugIn::OnLoadPlugIn().
	BOOL InitInstance() override;
  
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance clean up belongs here. 
  // All other significant cleanup should take place in either
  // CSelectPointsPlugIn::OnSaveAllSettings() or
  // CSelectPointsPlugIn::OnUnloadPlugIn().  
	int ExitInstance() override;
  
	DECLARE_MESSAGE_MAP()
};
