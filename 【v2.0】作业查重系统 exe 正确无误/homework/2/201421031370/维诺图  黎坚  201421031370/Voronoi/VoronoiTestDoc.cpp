// VoronoiTestDoc.cpp : implementation of the CVoronoiTestDoc class
//

#include "stdafx.h"
#include "VoronoiTest.h"

#include "MainFrm.h"
#include "VoronoiTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int MAX_SITES = 10000;

int compare(const void* arg1, const void* arg2)
{
	Site* site1 = (Site *) arg1;
	Site* site2 = (Site *) arg2;

	if (site1->m_pos.y < site2->m_pos.y) return ( 1);
	if (site1->m_pos.y > site2->m_pos.y) return (-1);
	if (site1->m_pos.x < site2->m_pos.x) return ( 1);
	if (site1->m_pos.x > site2->m_pos.x) return (-1);
	return (0);
}

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestDoc

IMPLEMENT_DYNCREATE(CVoronoiTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CVoronoiTestDoc, CDocument)
	//{{AFX_MSG_MAP(CVoronoiTestDoc)
	ON_COMMAND(ID_VIEW_TRIANGLE, OnViewTriangle)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TRIANGLE, OnUpdateViewTriangle)
	ON_COMMAND(ID_VIEW_VORONOI, OnViewVoronoi)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VORONOI, OnUpdateViewVoronoi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestDoc construction/destruction

CVoronoiTestDoc::CVoronoiTestDoc()
{
	m_nSites = 0;
	m_pSites = new Site[MAX_SITES];

	m_nEdges = 0;
	m_pEdges = NULL;
	m_pVoronoi = NULL;

	m_ptMin = Vector(0.0, 0.0);
	m_ptSize = Vector(200.0, 200.0);

	m_bShowVoronoi = TRUE;
	m_bShowTriangle = TRUE;
}

CVoronoiTestDoc::~CVoronoiTestDoc()
{
	SAFE_DELETE(m_pSites);
	SAFE_DELETE(m_pVoronoi);
}

BOOL CVoronoiTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_nSites = 0;
	m_pSites = new Site[MAX_SITES];

	m_nEdges = 0;
	m_pEdges = NULL;
	m_pVoronoi = NULL;

	return TRUE;
}

void CVoronoiTestDoc::DeleteContents() 
{
	m_nSites = 0;
	m_nEdges = 0;
	SAFE_DELETE(m_pSites);
	SAFE_DELETE(m_pVoronoi);
	
	CDocument::DeleteContents();
}

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestDoc serialization

void CVoronoiTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestDoc diagnostics

#ifdef _DEBUG
void CVoronoiTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVoronoiTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVoronoiTestDoc commands

void CVoronoiTestDoc::InitializeView(CRect &rect)
{
	m_viewSize.cx = rect.Width();
	m_viewSize.cy = rect.Height();
	m_ptSize.y = m_ptSize.x * m_viewSize.cy / m_viewSize.cx;

}

void CVoronoiTestDoc::AddNewSite(CPoint point)
{
	Vector1 pos;
	pos.x = (float) point.x / (float) m_viewSize.cx * m_ptSize.x + m_ptMin.x;
	pos.y = (float) point.y / (float) m_viewSize.cy * m_ptSize.y + m_ptMin.y;
	m_pSites[m_nSites].m_nid = m_nSites;
	m_pSites[m_nSites].m_pos = pos;
	m_nSites++;
	CalculateVoronoi();
}

void CVoronoiTestDoc::DrawSites(CDC *pDC)
{
	CPoint point;
	CPen pen(PS_SOLID, 0, RGB(0, 0, 0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));

	for (int i = 0; i < m_nSites; i++)
	{
		point.x = (int)((m_pSites[i].m_pos.x - m_ptMin.x) * m_viewSize.cx / m_ptSize.x);
		point.y = (int)((m_pSites[i].m_pos.y - m_ptMin.y) * m_viewSize.cy / m_ptSize.y);
		CRect rect(point.x-2, point.y-2, point.x+3, point.y+3);
		CPen* pOldPen = pDC->SelectObject(&pen);
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		pDC->Ellipse(&rect);
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}
}

void CVoronoiTestDoc::DrawEdges(CDC* pDC)
{
	if (m_nEdges != 0)
	{
		for (int i = 0; i < m_nEdges; i++)
		{
			if (m_bShowVoronoi && (m_pEdges[i].m_pEnd[0] != NULL) && (m_pEdges[i].m_pEnd[1] != NULL))
			{
				DrawLine(pDC, &m_pEdges[i].m_pEnd[0]->m_pos, &m_pEdges[i].m_pEnd[1]->m_pos, RGB(255, 0, 0));
			}
			if (m_bShowTriangle)
			{
				DrawLine(pDC, &m_pEdges[i].m_pReg[0]->m_pos, &m_pEdges[i].m_pReg[1]->m_pos, RGB(0, 0, 255));
			}
		}
	}
}

void CVoronoiTestDoc::CalculateVoronoi() 
{
	if (m_nSites < 2) return;

	qsort(m_pSites, m_nSites, sizeof(Site), compare);
	for (int i = 0; i < m_nSites; i++)
	{
		m_pSites[i].m_nid = i;
	}

	SAFE_DELETE(m_pVoronoi);
	m_pVoronoi = new CVoronoi();
	m_pVoronoi->InitEventHeap(m_nSites, m_pSites);
	m_pVoronoi->Process(&m_nEdges, &m_pEdges);
	UpdateAllViews(NULL);
}

void CVoronoiTestDoc::DrawLine(CDC *pDC, Vector* pos1, Vector* pos2, COLORREF clrLine)
{
	CPoint point1, point2;
	CPen pen(PS_SOLID, 0, clrLine);
	CPen* oldPen = pDC->SelectObject(&pen);

	point1.x = (int)((pos1->x - m_ptMin.x) * m_viewSize.cx / m_ptSize.x);
	point1.y = (int)((pos1->y - m_ptMin.y) * m_viewSize.cy / m_ptSize.y);
	point2.x = (int)((pos2->x - m_ptMin.x) * m_viewSize.cx / m_ptSize.x);
	point2.y = (int)((pos2->y - m_ptMin.y) * m_viewSize.cy / m_ptSize.y);
	pDC->MoveTo(point1);
	pDC->LineTo(point2);

	pDC->SelectObject(oldPen);
}

void CVoronoiTestDoc::OnViewTriangle() 
{
	m_bShowTriangle = !m_bShowTriangle;
	UpdateAllViews(NULL);
	
}

void CVoronoiTestDoc::OnUpdateViewTriangle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShowTriangle);
	
}

void CVoronoiTestDoc::OnViewVoronoi() 
{
	m_bShowVoronoi = !m_bShowVoronoi;
	UpdateAllViews(NULL);
	
}

void CVoronoiTestDoc::OnUpdateViewVoronoi(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShowVoronoi);
	
}
