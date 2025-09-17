
// lab_1_OS.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Clab1OSApp:
// See lab_1_OS.cpp for the implementation of this class
//

class Clab1OSApp : public CWinApp
{
public:
	Clab1OSApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Clab1OSApp theApp;
