// VoronoiTestDoc.h : interface of the CVoronoiTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VORONOITESTDOC_H__3FE1C18B_CE39_11D5_83A3_000347397404__INCLUDED_)
#define AFX_VORONOITESTDOC_H__3FE1C18B_CE39_11D5_83A3_000347397404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "voronoi.h"

class CVoronoiTestDoc : public CDocument
{
protected: // create from serialization only
	CVoronoiTestDoc();
	DECLARE_DYNCREATE(CVoronoiTestDoc)

// Attributes
public:
	virtual ~CVoronoiTestDoc();

// Operations
public:
	void DrawLine(CDC* pDC, Vector* pos1, Vector* pos2, COLORREF clrLine);
	void DrawEdges(CDC* pDC);
	void DrawSites(CDC* pDC);
	void CalculateVoronoi();
	void AddNewSite(CPoint point);
	void InitializeView(CRect& rect);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoronoiTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int		m_nSites;
	Site*	m_pSites;

	int		m_nEdges;
	Edge*	m_pEdges;

	CVoronoi*	m_pVoronoi;

	Vector1 m_ptMin;
	Vector1 m_ptSize;
	CSize	m_viewSize;

	BOOL	m_bShowVoronoi;
	BOOL	m_bShowTriangle;

// Generated message map functions
protected:
	//{{AFX_MSG(CVoronoiTestDoc)
	afx_msg void OnViewTriangle();
	afx_msg void OnUpdateViewTriangle(CCmdUI* pCmdUI);
	afx_msg void OnViewVoronoi();
	afx_msg void OnUpdateViewVoronoi(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VORONOITESTDOC_H__3FE1C18B_CE39_11D5_83A3_000347397404__INCLUDED_)
