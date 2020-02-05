
// 3170106249SX15.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy3170106249SX15App:
// See 3170106249SX15.cpp for the implementation of this class
//

class CMy3170106249SX15App : public CWinApp
{
public:
	CMy3170106249SX15App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy3170106249SX15App theApp;
