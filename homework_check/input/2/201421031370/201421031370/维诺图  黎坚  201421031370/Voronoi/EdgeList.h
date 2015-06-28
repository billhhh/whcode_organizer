// EdgeList.h: interface for the EdgeList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGELIST_H__3FE1C196_CE39_11D5_83A3_000347397404__INCLUDED_)
#define AFX_EDGELIST_H__3FE1C196_CE39_11D5_83A3_000347397404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	LEFTSIDE		0
#define	RIGHTSIDE		1

inline BOOL FP_EQ(float s, float t)
{
	return (fabsf(s - t) <= fEpsilon);
}

inline BOOL FP_NE(float s, float t)
{
	return !FP_EQ(s, t);
}

inline BOOL FP_GT(float s, float t)
{
	return ((s - t) > fEpsilon);
}

inline BOOL FP_GE(float s, float t)
{
	return ((s - t) >= - fEpsilon);
}

inline BOOL FP_LT(float s, float t)
{
	return ((s - t) < - fEpsilon);
}

inline BOOL FP_LE(float s, float t)
{
	return ((s - t) <= fEpsilon);
}

class CEvent;
class CCircleEvent;
class CVoronoi;

struct Site
{
	int		m_nid;
	Vector1 m_pos;
};

inline float dist(Site *s, Site *t)
{
	return length(s->m_pos - t->m_pos);
}

struct Edge
{
	int		m_nid;
	float	a, b, c;
	Vector1 m_initPos;
	Site*	m_pEnd[2];
	Site*	m_pReg[2];
	CCircleEvent* m_pLEvent;		// circle event on left extent of edge
	CCircleEvent* m_pREvent;		// circle event on right extent of edge
};

struct HalfEdge  
{
	HalfEdge(Edge* pEdge, Site* pSite)
	{
		m_pEdge = pEdge;
		m_pLeft = NULL;
		m_pRight = NULL;
		m_pNext = NULL;
		m_pSite = pSite;
		m_pEvent = NULL;
	};

	Edge*		m_pEdge;	// this pointer points edge on the right side of halfedge defined here
	HalfEdge*	m_pLeft;
	HalfEdge*	m_pRight;
	HalfEdge*	m_pNext;
	Site*		m_pSite;
	CCircleEvent* m_pEvent;	// pointer to circle for which this halfedge is center edge.
};

class EdgeList  
{
public:
	EdgeList(CVoronoi* pVoronoi);
	virtual ~EdgeList();

public:
	BOOL		IsEmpty() { return (m_nEdgeCount == 0); };
	void		InitEdgeList(HalfEdge* newHEdge);
	void		Delete(HalfEdge* pHEdge);
	HalfEdge*	Insert(HalfEdge* leftBound, HalfEdge* newHEdge);
	HalfEdge*	ExtractHalfEdge(HalfEdge* pHEdge);
	HalfEdge*	FindHalfEdgeAbove(Site* pSite, Vector* vecPos);
	HalfEdge*	GetFirstHalfEdge() { return m_pLeftEnd; };
	HalfEdge*	GetNextEdge(HalfEdge* pHEdge) { return pHEdge->m_pRight; };
	CCircleEvent* CircleEventOnLeftOfSiteEvent(Edge* pEdge, HalfEdge* pHEdge, float ypos);
	CCircleEvent* CircleEventOnRightOfSiteEvent(Edge* pEdge, HalfEdge* pHEdge, float ypos);
	CCircleEvent* CircleEventOnLeftOfCircleEvent(Edge* pEdge, HalfEdge* pHEdge, float ypos, Vector vec, Site* site);
	CCircleEvent* CircleEventOnRightOfCircleEvent(Edge* pEdge, HalfEdge* pHEdge, float ypos, Vector vec, Site* site);

private:
	int			m_nEdgeCount;
	HalfEdge*	m_pLeftEnd;
	HalfEdge*	m_pRightEnd;
	CVoronoi*	m_pVoronoi;

private:
	void		RemoveNext(HalfEdge* pNext);
	BOOL		GetCircleFromTwoPointsAndTangent(Vector* pc, float* radius, Vector* p1, Vector* p2, float y0, BOOL bSide);
	BOOL		GetCircleFromThreePoints(Vector* pc, float* radius, Vector* p1, Vector* p2, Vector* p3);
	CCircleEvent* GetCircleEvent(HalfEdge* pHEdge1, HalfEdge* pHEdge2, HalfEdge* pHEdge3, float ypos);
};

#endif // !defined(AFX_EDGELIST_H__3FE1C196_CE39_11D5_83A3_000347397404__INCLUDED_)
