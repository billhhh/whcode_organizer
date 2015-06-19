// VoronoiTest.h : main header file for the VORONOITEST application
//

#if !defined(AFX_VORONOITEST_H__3FE1C185_CE39_11D5_83A3_000347397404__INCLUDED_)
#define AFX_VORONOITEST_H__3FE1C185_CE39_11D5_83A3_000347397404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include <math.h>
#define fHuge		1e+38f
#define fEpsilon	1e-8f
#include "Vector.h"

#define SAFE_DELETE(x)	{if ((x) != NULL) { delete (x); (x) = NULL; }}

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestApp:
// See VoronoiTest.cpp for the implementation of this class
//

class CVoronoiTestApp : public CWinApp
{
public:
	CVoronoiTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoronoiTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVoronoiTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VORONOITEST_H__3FE1C185_CE39_11D5_83A3_000347397404__INCLUDED_)
