// Voronoi.h: interface for the CVoronoi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VORONOI_H__3FE1C197_CE39_11D5_83A3_000347397404__INCLUDED_)
#define AFX_VORONOI_H__3FE1C197_CE39_11D5_83A3_000347397404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EdgeList.h"
#include "EventHeap.h"

#define SINGLE_STEP_DONE			0
#define SINGLE_STEP_IN_PROGRESS		1

class CVoronoiTestDoc;

class CVoronoi  
{
public:
	CVoronoi();
	virtual ~CVoronoi();

public:
	int		Process(int* pnEdges, Edge** ppEdges);
	void	RemoveCircleEvent(CCircleEvent* pEvent);
	void	AddNewEvent(CEvent* pNewEvent, BOOL bSort = FALSE);
	void	InitEventHeap(int nsites, Site* pSiteList);
	Site*	CreateNewSite(const Vector& pos);
	Edge*	CreateNewEdge(const Vector& pos);

private:
	int			m_nEdges;
	int			m_nSites;
	Edge*		m_pEdges;
	Site*		m_pSites;
	EdgeList*	m_pEdgeList;
	CEventHeap*	m_pEventHeap;
};

#endif // !defined(AFX_VORONOI_H__3FE1C197_CE39_11D5_83A3_000347397404__INCLUDED_)
