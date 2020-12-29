
// TextStats.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTextStatsApp:
// See TextStats.cpp for the implementation of this class
//

class CTextStatsApp : public CWinApp
{
public:
	CTextStatsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTextStatsApp theApp;
