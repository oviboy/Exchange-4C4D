// BRD2007.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CBRD2007App:
// See BRD2007.cpp for the implementation of this class
//

class CBRD2007App : public CWinApp
{
public:
	CBRD2007App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CBRD2007App theApp;
