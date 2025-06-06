// BrepSelector.h : main header file for the BrepSelector DLL.
//

#pragma once


#include "resource.h" // main symbols

// CBrepSelectorApp
// See BrepSelectorApp.cpp for the implementation of this class
//

class CBrepSelectorApp : public CWinApp
{
public:
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance construction belongs here. 
  // All other significant initialization should take place in
  // CBrepSelectorPlugIn::OnLoadPlugIn().
	CBrepSelectorApp() = default;

  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance initialization belongs here. 
  // All other significant initialization should take place in
  // CBrepSelectorPlugIn::OnLoadPlugIn().
	BOOL InitInstance() override;
  
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance clean up belongs here. 
  // All other significant cleanup should take place in either
  // CBrepSelectorPlugIn::OnSaveAllSettings() or
  // CBrepSelectorPlugIn::OnUnloadPlugIn().  
	int ExitInstance() override;
  
	DECLARE_MESSAGE_MAP()
};
