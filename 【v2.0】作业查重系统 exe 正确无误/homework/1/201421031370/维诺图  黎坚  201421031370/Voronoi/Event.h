// Event.h: interface for the CEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENT_H__9C8CC471_CEF1_11D5_83A3_000347397404__INCLUDED_)
#define AFX_EVENT_H__9C8CC471_CEF1_11D5_83A3_000347397404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct Site;
struct HalfEdge;
class EdgeList;
class CVoronoi;

class CEvent  
{
public:
	CEvent();
	virtual ~CEvent();

public:
	virtual void HandleEvent(EdgeList* pEdgeList, CVoronoi* pVoronoi);

//protected:
	float	m_yvalue;
	CEvent*	m_pNext;

};

class CSiteEvent : public CEvent  
{
public:
	CSiteEvent();
	virtual ~CSiteEvent();

public:
	virtual void HandleEvent(EdgeList* pEdgeList, CVoronoi* pVoronoi);

//protected:
	Site*	m_pSite;

};

class CCircleEvent : public CEvent  
{
public:
	CCircleEvent();
	CCircleEvent(const Vector& center, float yvalue);
	virtual ~CCircleEvent();

public:
	virtual void HandleEvent(EdgeList* pEdgeList, CVoronoi* pVoronoi);

//protected:
	Vector1		m_ptCenter;
	HalfEdge*	m_pHEdge[3];
};

#endif // !defined(AFX_EVENT_H__9C8CC471_CEF1_11D5_83A3_000347397404__INCLUDED_)
