// CarSim.h : main header file for the CARSIM application
//

#if !defined(AFX_CARSIM_H__C2FF8161_9A14_47F8_9212_11E5AD79001E__INCLUDED_)
#define AFX_CARSIM_H__C2FF8161_9A14_47F8_9212_11E5AD79001E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCarSimApp:
// See CarSim.cpp for the implementation of this class
//

class CCarSimApp : public CWinApp
{
public:
	CCarSimApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCarSimApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCarSimApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARSIM_H__C2FF8161_9A14_47F8_9212_11E5AD79001E__INCLUDED_)
