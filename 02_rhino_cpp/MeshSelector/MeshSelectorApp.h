// MeshSelector.h : main header file for the MeshSelector DLL.
//

#pragma once


#include "resource.h" // main symbols

// CMeshSelectorApp
// See MeshSelectorApp.cpp for the implementation of this class
//

class CMeshSelectorApp : public CWinApp
{
public:
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance construction belongs here. 
  // All other significant initialization should take place in
  // CMeshSelectorPlugIn::OnLoadPlugIn().
	CMeshSelectorApp() = default;

  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance initialization belongs here. 
  // All other significant initialization should take place in
  // CMeshSelectorPlugIn::OnLoadPlugIn().
	BOOL InitInstance() override;
  
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance clean up belongs here. 
  // All other significant cleanup should take place in either
  // CMeshSelectorPlugIn::OnSaveAllSettings() or
  // CMeshSelectorPlugIn::OnUnloadPlugIn().  
	int ExitInstance() override;
  
	DECLARE_MESSAGE_MAP()
};
