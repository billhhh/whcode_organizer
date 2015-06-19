// Voronoi.cpp: implementation of the CVoronoi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoronoiTest.h"
#include "Voronoi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const int MAX_EDGES = 10000;
static const int MAX_SITES = 10000;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVoronoi::CVoronoi()
{
	m_nEdges = 0;
	m_nSites = 0;
	m_pEdges = new Edge[MAX_EDGES];
	m_pSites = new Site[MAX_SITES];
	m_pEdgeList  = new EdgeList(this);
	m_pEventHeap = new CEventHeap(this);
}

CVoronoi::~CVoronoi()
{
	SAFE_DELETE(m_pEdges);
	SAFE_DELETE(m_pSites);
	SAFE_DELETE(m_pEdgeList);
	SAFE_DELETE(m_pEventHeap);

}

void CVoronoi::InitEventHeap(int nsites, Site* SiteList)
{
	for (int i = 0; i < nsites; i++)
	{
		CSiteEvent* newEvent = new CSiteEvent();
		newEvent->m_pSite = &SiteList[i];
		newEvent->m_yvalue = SiteList[i].m_pos.y;
		m_pEventHeap->AddNewEvent(newEvent);
	}
}

int CVoronoi::Process(int* pnEdges, Edge** ppEdges)
{
	CEvent* pNextEvent;

	while ((pNextEvent = m_pEventHeap->GetNextEvent()) != NULL)
	{
		pNextEvent->HandleEvent(m_pEdgeList, this);
		SAFE_DELETE(pNextEvent);
	}

	*pnEdges = m_nEdges;
	*ppEdges = m_pEdges;
	return 0;
}

Edge* CVoronoi::CreateNewEdge(const Vector& pos)
{
	if (m_nEdges < MAX_EDGES-1)
	{
		m_pEdges[m_nEdges].m_nid = m_nEdges;
		m_pEdges[m_nEdges].m_initPos = pos;
		m_pEdges[m_nEdges].m_pEnd[0] = NULL;
		m_pEdges[m_nEdges].m_pEnd[1] = NULL;
		m_pEdges[m_nEdges].m_pLEvent = NULL;
		m_pEdges[m_nEdges].m_pREvent = NULL;
		return &m_pEdges[m_nEdges++];
	}
	else
	{
		ASSERT(FALSE);
		return NULL;
	}
}

Site* CVoronoi::CreateNewSite(const Vector& pos)
{
	if (m_nSites < MAX_SITES-1)
	{
		m_pSites[m_nSites].m_nid = m_nSites;
		m_pSites[m_nSites].m_pos = pos;
		return &m_pSites[m_nSites++];
	}
	else
	{
		ASSERT(FALSE);
		return NULL;
	}
}

void CVoronoi::AddNewEvent(CEvent *pNewEvent, BOOL bSort)
{
	m_pEventHeap->AddNewEvent(pNewEvent, bSort);
}

void CVoronoi::RemoveCircleEvent(CCircleEvent* pEvent)
{
	m_pEventHeap->RemoveCircleEvent(pEvent);
}
