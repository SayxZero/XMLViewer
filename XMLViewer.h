
// XMLViewer.h : main header file for the XMLViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CXMLViewerApp:
// See XMLViewer.cpp for the implementation of this class
//

class CXMLViewerApp : public CWinApp
{
public:
	CXMLViewerApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CXMLViewerApp theApp;
