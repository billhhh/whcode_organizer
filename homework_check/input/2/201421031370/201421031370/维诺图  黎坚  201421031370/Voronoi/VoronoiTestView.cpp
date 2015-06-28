// VoronoiTestView.cpp : implementation of the CVoronoiTestView class
//

#include "stdafx.h"
#include "VoronoiTest.h"

#include "VoronoiTestDoc.h"
#include "VoronoiTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestView

IMPLEMENT_DYNCREATE(CVoronoiTestView, CView)

BEGIN_MESSAGE_MAP(CVoronoiTestView, CView)
	//{{AFX_MSG_MAP(CVoronoiTestView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestView construction/destruction

CVoronoiTestView::CVoronoiTestView()
{
	// TODO: add construction code here

}

CVoronoiTestView::~CVoronoiTestView()
{
}

BOOL CVoronoiTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestView drawing

void CVoronoiTestView::OnDraw(CDC* pDC)
{
	CVoronoiTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rc;
	CDC dcMem;
	CBitmap bmp;
	CBrush brBkGnd;

	GetClientRect(&rc);

	// Create compatible DC and select bitmap for the off-screen DC
	dcMem.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	CBitmap* pOldBitmap = dcMem.SelectObject(&bmp);

	// Erase the background
	brBkGnd.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	dcMem.FillRect(&rc, &brBkGnd);
	
	pDoc->DrawSites(&dcMem);
	pDoc->DrawEdges(&dcMem);

	pDC->BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &dcMem, 0, 0, SRCCOPY);
	dcMem.SelectObject(pOldBitmap);}

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestView printing

BOOL CVoronoiTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVoronoiTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVoronoiTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestView diagnostics

#ifdef _DEBUG
void CVoronoiTestView::AssertValid() const
{
	CView::AssertValid();
}

void CVoronoiTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVoronoiTestDoc* CVoronoiTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVoronoiTestDoc)));
	return (CVoronoiTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestView message handlers

void CVoronoiTestView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CVoronoiTestDoc* pDoc = GetDocument();
	pDoc->AddNewSite(point);
	Invalidate();
	
	CView::OnLButtonDown(nFlags, point);
}

void CVoronoiTestView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	CRect rect;
	CVoronoiTestDoc* pDoc = GetDocument();

	GetClientRect(rect);
	pDoc->InitializeView(rect);
	
}

BOOL CVoronoiTestView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
