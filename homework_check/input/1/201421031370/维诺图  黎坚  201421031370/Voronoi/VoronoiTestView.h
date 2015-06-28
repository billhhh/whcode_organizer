// VoronoiTestView.h : interface of the CVoronoiTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VORONOITESTVIEW_H__3FE1C18D_CE39_11D5_83A3_000347397404__INCLUDED_)
#define AFX_VORONOITESTVIEW_H__3FE1C18D_CE39_11D5_83A3_000347397404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVoronoiTestView : public CView
{
protected: // create from serialization only
	CVoronoiTestView();
	DECLARE_DYNCREATE(CVoronoiTestView)

// Attributes
public:
	CVoronoiTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoronoiTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVoronoiTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVoronoiTestView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VoronoiTestView.cpp
inline CVoronoiTestDoc* CVoronoiTestView::GetDocument()
   { return (CVoronoiTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VORONOITESTVIEW_H__3FE1C18D_CE39_11D5_83A3_000347397404__INCLUDED_)
