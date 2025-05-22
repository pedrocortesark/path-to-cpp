// CreatePoints.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CreatePointsApp.h"

//
//	Note!
//
//    A Rhino plug-in is an MFC DLL.
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CCreatePointsApp

BEGIN_MESSAGE_MAP(CCreatePointsApp, CWinApp)
END_MESSAGE_MAP()

// The one and only CCreatePointsApp object
CCreatePointsApp theApp;

// CCreatePointsApp initialization

BOOL CCreatePointsApp::InitInstance()
{
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance initialization belongs here. 
  // All other significant initialization should take place in
  // CCreatePointsPlugIn::OnLoadPlugIn().

	CWinApp::InitInstance();

	return TRUE;
}

int CCreatePointsApp::ExitInstance()
{
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance clean up belongs here. 
  // All other significant cleanup should take place in either
  // CCreatePointsPlugIn::OnSaveAllSettings() or
  // CCreatePointsPlugIn::OnUnloadPlugIn().
  return CWinApp::ExitInstance();
}
