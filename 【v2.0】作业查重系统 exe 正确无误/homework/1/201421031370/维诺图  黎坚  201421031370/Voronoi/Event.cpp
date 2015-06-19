// Event.cpp: implementation of the CEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoronoiTest.h"

#include "EdgeList.h"
#include "Event.h"
#include "Voronoi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEvent::CEvent()
{
	m_pNext = NULL;
}

CEvent::~CEvent()
{

}

void CEvent::HandleEvent(EdgeList* pEdgeList, CVoronoi* pVoronoi)
{

}

//////////////////////////////////////////////////////////////////////
// CSiteEvent Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSiteEvent::CSiteEvent()
{
	m_pSite = NULL;
}

CSiteEvent::~CSiteEvent()
{

}

void CSiteEvent::HandleEvent(EdgeList* pEdgeList, CVoronoi* pVoronoi)
{
//	TRACE("Handling Site Event at (%f, %f)\n",m_pSite->m_pos.x, m_pSite->m_pos.y);
	if (pEdgeList->IsEmpty())
	{
		HalfEdge* pNewEdge = new HalfEdge(NULL, m_pSite);
		pEdgeList->InitEdgeList(pNewEdge);
		return;
	}

	Site* oldSite;
	Vector vecPos;
	HalfEdge* oldHEdge;
	HalfEdge* pExtract;
	CCircleEvent* pEvent;
		
	// Search the tree for halfedge vertically above the site
	oldHEdge = pEdgeList->FindHalfEdgeAbove(m_pSite, &vecPos);
	ASSERT(oldHEdge != NULL);
	pExtract = pEdgeList->ExtractHalfEdge(oldHEdge);
	oldSite = oldHEdge->m_pSite;

	Edge* newEdge = pVoronoi->CreateNewEdge(vecPos);
	newEdge->m_pReg[0] = oldSite;
	newEdge->m_pReg[1] = m_pSite;

	float x1, x2, y1, y2;
	x1 = oldSite->m_pos.x;
	y1 = oldSite->m_pos.y;
	x2 = m_pSite->m_pos.x;
	y2 = m_pSite->m_pos.y;

	newEdge->a = x2 - x1;
	newEdge->b = y2 - y1;
	newEdge->c = 0.5f*(x2*x2-x1*x1+y2*y2-y1*y1);

	HalfEdge* newHEdge  = new HalfEdge(newEdge, m_pSite);
	HalfEdge* oldHEdge1 = new HalfEdge(newEdge, oldSite);

	if ((pEvent = oldHEdge->m_pEvent) != NULL)
	{
		pVoronoi->RemoveCircleEvent(pEvent);
		oldHEdge->m_pEvent = NULL;
	}

	else if ((oldHEdge->m_pLeft != NULL) && ((pEvent = oldHEdge->m_pLeft->m_pEvent) != NULL))
	{
		pEvent->m_pHEdge[2] = oldHEdge1;
	}
	pExtract = pEdgeList->Insert(pExtract, oldHEdge);	// Order is:
	pExtract = pEdgeList->Insert(pExtract, newHEdge);	// oldHEdge1 <-> newHEdge <-> oldHEdge
	pExtract = pEdgeList->Insert(pExtract, oldHEdge1);

	if ((pEvent = pEdgeList->CircleEventOnLeftOfSiteEvent(newEdge, newHEdge, m_pSite->m_pos.y)) != NULL)
	{
//		TRACE("        Adding Cricle Event at (%f, %f) with HEdges 0x%x, 0x%x, 0x%x\n",pEvent->m_ptCenter.x,pEvent->m_ptCenter.y, pEvent->m_pHEdge[0], pEvent->m_pHEdge[1], pEvent->m_pHEdge[2]);
		pVoronoi->AddNewEvent(pEvent, TRUE);
	}
	if ((pEvent = pEdgeList->CircleEventOnRightOfSiteEvent(newEdge, newHEdge, m_pSite->m_pos.y)) != NULL)
	{
//		TRACE("        Adding Cricle Event at (%f, %f) with HEdges 0x%x, 0x%x, 0x%x\n",pEvent->m_ptCenter.x,pEvent->m_ptCenter.y, pEvent->m_pHEdge[0], pEvent->m_pHEdge[1], pEvent->m_pHEdge[2]);
		pVoronoi->AddNewEvent(pEvent, TRUE);
	}
}

//////////////////////////////////////////////////////////////////////
// CCircleEvent Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircleEvent::CCircleEvent()
{
	m_pHEdge[0] = NULL;
	m_pHEdge[1] = NULL;
	m_pHEdge[2] = NULL;
}

CCircleEvent::CCircleEvent(const Vector& center, float yvalue)
{
	m_ptCenter = center;
	m_yvalue = yvalue;

	m_pHEdge[0] = NULL;
	m_pHEdge[1] = NULL;
	m_pHEdge[2] = NULL;
}

CCircleEvent::~CCircleEvent()
{

}

void CCircleEvent::HandleEvent(EdgeList* pEdgeList, CVoronoi* pVoronoi)
{
//	TRACE("Handling Cricle Event at (%f, %f) with HEdges 0x%x, 0x%x, 0x%x\n",m_ptCenter.x,m_ptCenter.y, m_pHEdge[0], m_pHEdge[1], m_pHEdge[2]);
	Site* pSite = pVoronoi->CreateNewSite(m_ptCenter);

	// clear all pointers linked to this event
	for (int i = 0; i < 2; i++)
	{
		Edge* pEdge = m_pHEdge[i]->m_pEdge;
		if (pEdge->m_pREvent == this) pEdge->m_pREvent = NULL;
		else if (pEdge->m_pLEvent == this) pEdge->m_pLEvent = NULL;

		if (pEdge->m_pEnd[0] == NULL) pEdge->m_pEnd[0] = pSite;
		else pEdge->m_pEnd[1] = pSite;
	}
	m_pHEdge[1]->m_pEvent = NULL;

	Edge* newEdge = pVoronoi->CreateNewEdge(m_ptCenter);
	newEdge->m_pEnd[0] = pSite;
	newEdge->m_pReg[0] = m_pHEdge[0]->m_pSite;
	newEdge->m_pReg[1] = m_pHEdge[2]->m_pSite;

	Vector vec, vec1, vec2;
	vec1 = m_pHEdge[0]->m_pSite->m_pos;
	vec2 = m_pHEdge[2]->m_pSite->m_pos;
	newEdge->a = vec2.x - vec1.x;
	newEdge->b = vec2.y - vec1.y;
	newEdge->c = 0.5f*(vec2.x*vec2.x - vec1.x*vec1.x + vec2.y*vec2.y - vec1.y*vec1.y);

	vec1 = m_pHEdge[0]->m_pEdge->m_initPos - m_ptCenter;
	vec2 = m_pHEdge[1]->m_pEdge->m_initPos - m_ptCenter;

	vec1.Normalize();
	vec2.Normalize();

	vec = vec1 + vec2;
	vec.Normalize();

	Site* site = m_pHEdge[1]->m_pSite;

	m_pHEdge[0]->m_pEdge = newEdge;
	pEdgeList->Delete(m_pHEdge[1]);

	CCircleEvent* pEvent;

	if ((pEvent = pEdgeList->CircleEventOnLeftOfCircleEvent(newEdge, m_pHEdge[2], m_yvalue, vec, site)) != NULL)
	{
//		TRACE("        Adding Cricle Event at (%f, %f) with HEdges 0x%x, 0x%x, 0x%x\n",pEvent->m_ptCenter.x,pEvent->m_ptCenter.y, pEvent->m_pHEdge[0], pEvent->m_pHEdge[1], pEvent->m_pHEdge[2]);
		pVoronoi->AddNewEvent(pEvent, TRUE);
	}
	if ((pEvent = pEdgeList->CircleEventOnRightOfCircleEvent(newEdge, m_pHEdge[0], m_yvalue, vec, site)) != NULL)
	{
//		TRACE("        Adding Cricle Event at (%f, %f) with HEdges 0x%x, 0x%x, 0x%x\n",pEvent->m_ptCenter.x,pEvent->m_ptCenter.y, pEvent->m_pHEdge[0], pEvent->m_pHEdge[1], pEvent->m_pHEdge[2]);
		pVoronoi->AddNewEvent(pEvent, TRUE);
	}
}
