// EdgeList.cpp: implementation of the EdgeList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoronoiTest.h"

#include "EdgeList.h"
#include "EventHeap.h"
#include "Voronoi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EdgeList::EdgeList(CVoronoi* pVoronoi)
{
	m_nEdgeCount = 0;
	m_pLeftEnd = NULL;
	m_pRightEnd = NULL;
	m_pVoronoi = pVoronoi;

}

EdgeList::~EdgeList()
{
	if (m_pLeftEnd != NULL)
	{
		RemoveNext(m_pLeftEnd);
	}
	m_nEdgeCount = 0;
}

HalfEdge* EdgeList::FindHalfEdgeAbove(Site *pSite, Vector* vecPos)
{
	float dist, dx, dy;
	float mindist = fHuge;
	HalfEdge* pNext;

	pNext = m_pLeftEnd;
	HalfEdge* pMinHE = NULL;
	while (pNext != NULL)
	{
		dx = pSite->m_pos.x - pNext->m_pSite->m_pos.x;
		dy = pSite->m_pos.y - pNext->m_pSite->m_pos.y;
		if (FP_EQ(dy, 0.0f)) dy = fEpsilon;
		dist = 0.5f*(dy + dx*dx/dy);
		if (FP_LE(dist, mindist))
		{
			HalfEdge* pHENext;
			if (FP_LT(dist, mindist))	// found new site with closer halfedge
			{
				pMinHE = pNext;
				pHENext = pMinHE;
				pHENext->m_pNext = NULL;
				mindist = dist;
			}
			else						// found different halfedge from site with minimum distance
			{
				pHENext->m_pNext = pNext;
				pHENext = pHENext->m_pNext;
				pHENext->m_pNext = NULL;
			}
		}
		pNext = pNext->m_pRight;
	}
	if (pMinHE == NULL) return NULL;

	vecPos->x = pSite->m_pos.x;
	vecPos->y = pSite->m_pos.y - mindist;
	if (pMinHE->m_pNext == NULL) return pMinHE;

	// We found a list of halfedges who are using same site ad one we are looking for
	// Now are going to select one from the list which is located above current site.
	pNext = pMinHE;
	BOOL bDone = FALSE;
	HalfEdge* pAboveHE = NULL;
	while (pNext != NULL && !bDone)
	{
		if (pNext->m_pNext == NULL)
		{
			pAboveHE = pNext;
			bDone = TRUE;
		}
		else
		{
			float radius;
			Vector center;
			Site* s1 = pNext->m_pSite;
			Site* s2 = pNext->m_pRight->m_pSite;

			BOOL bSide = FP_LT(s1->m_pos.y, s2->m_pos.y) ? RIGHTSIDE : LEFTSIDE;
			GetCircleFromTwoPointsAndTangent(&center, &radius, &s1->m_pos, &s2->m_pos, pSite->m_pos.y, bSide);
			if (FP_GT(center.x, pSite->m_pos.x))
			{
				pAboveHE = pNext;
				bDone = TRUE;
			}
			else
			{
				pNext = pNext->m_pNext;
			}
		}
	}

	return pAboveHE;
}

HalfEdge* EdgeList::ExtractHalfEdge(HalfEdge *pHEdge)
{
	HalfEdge* pLeft;

	if (pHEdge == m_pLeftEnd)
	{
		if (pHEdge == m_pRightEnd)
		{
			m_pLeftEnd = NULL;
			m_pRightEnd = NULL;
		}
		else
		{
			m_pLeftEnd = pHEdge->m_pRight;
			m_pLeftEnd->m_pLeft = NULL;
		}
		pLeft = NULL;
	}
	else
	{
		pLeft = pHEdge->m_pLeft;
		pLeft->m_pRight = pHEdge->m_pRight;
		if (pHEdge == m_pRightEnd)
		{
			m_pRightEnd = pLeft;
		}
		else
		{
			pHEdge->m_pRight->m_pLeft = pLeft;
		}
	}
	m_nEdgeCount--;
	return pLeft;
}

CCircleEvent* EdgeList::CircleEventOnLeftOfSiteEvent(Edge* pEdge, HalfEdge* pHEdge, float ypos)
{
	CCircleEvent* pEvent = NULL;
	HalfEdge* h1, * h2;
	HalfEdge* h0 = pHEdge;
	float a1, a2, b1, b2, c1, c2, x;

	if ((h1 = h0->m_pLeft) != NULL)
	{
		if ((h2 = h1->m_pLeft) != NULL)
		{
			a1 = h2->m_pEdge->a;
			b1 = h2->m_pEdge->b;
			c1 = h2->m_pEdge->c;
			a2 = h1->m_pEdge->a;
			b2 = h1->m_pEdge->b;
			c2 = h1->m_pEdge->c;
//			ASSERT(FP_NE(b2*a1, b1*a2));
			if (FP_EQ(a1*b2, a2*b1)) return NULL;
			x = (b2*c1 - b1*c2)/(a1*b2 - a2*b1);
			if (x < pEdge->m_initPos.x)
			{
				pEvent = GetCircleEvent(h2, h1, h0, ypos);
			}
		}
	}

	return pEvent;
}

CCircleEvent* EdgeList::CircleEventOnRightOfSiteEvent(Edge* pEdge, HalfEdge* pHEdge, float ypos)
{
	CCircleEvent* pEvent = NULL;
	HalfEdge* h1, * h2;
	HalfEdge* h0 = pHEdge;
	float a1, a2, b1, b2, c1, c2, x;

	if ((h1 = h0->m_pRight) != NULL)
	{
		if ((h2 = h1->m_pRight) != NULL)
		{
			a1 = h0->m_pEdge->a;
			b1 = h0->m_pEdge->b;
			c1 = h0->m_pEdge->c;
			a2 = h1->m_pEdge->a;
			b2 = h1->m_pEdge->b;
			c2 = h1->m_pEdge->c;
//			ASSERT(FP_NE(b2*a1, b1*a2));
			if (FP_EQ(a1*b2, a2*b1)) return NULL;
			x = (b2*c1 - b1*c2)/(a1*b2 - a2*b1);
			if (x > pEdge->m_initPos.x)
			{
				pEvent = GetCircleEvent(h0, h1, h2, ypos);
			}
		}
	}
	return pEvent;
}

CCircleEvent* EdgeList::CircleEventOnLeftOfCircleEvent(Edge* pEdge, HalfEdge* pHEdge, float ypos, Vector vec, Site* site)
{
	CCircleEvent* pEvent = NULL;
	HalfEdge* h1, * h2;
	HalfEdge* h0 = pHEdge;
	float a1, a2, b1, b2, c1, c2;
	Vector v0, v1;

	if ((h1 = h0->m_pLeft) != NULL)
	{
		if ((h2 = h1->m_pLeft) != NULL && h2->m_pSite != site)
		{
			a1 = h2->m_pEdge->a;
			b1 = h2->m_pEdge->b;
			c1 = h2->m_pEdge->c;
			a2 = h1->m_pEdge->a;
			b2 = h1->m_pEdge->b;
			c2 = h1->m_pEdge->c;
//			ASSERT(FP_NE(b2*a1, b1*a2));
			if (FP_EQ(a1*b2, a2*b1)) return NULL;
			v0.x = (b2*c1 - b1*c2)/(a1*b2 - a2*b1);
			v0.y = (a2*c1 - a1*c2)/(a2*b1 - a1*b2);
			v0 = v0 - pEdge->m_initPos;
			v0.Normalize();
			if (v0.x*vec.x + v0.y*vec.y < 0.0f)
			{
				pEvent = GetCircleEvent(h2, h1, h0, ypos);
			}
		}
	}

	return pEvent;
}

CCircleEvent* EdgeList::CircleEventOnRightOfCircleEvent(Edge* pEdge, HalfEdge* pHEdge, float ypos, Vector vec, Site* site)
{
	CCircleEvent* pEvent = NULL;
	HalfEdge* h1, * h2;
	HalfEdge* h0 = pHEdge;
	float a1, a2, b1, b2, c1, c2;
	Vector v0, v1;

	if ((h1 = h0->m_pRight) != NULL)
	{
		if ((h2 = h1->m_pRight) != NULL && h2->m_pSite != site)
		{
			a1 = h0->m_pEdge->a;
			b1 = h0->m_pEdge->b;
			c1 = h0->m_pEdge->c;
			a2 = h1->m_pEdge->a;
			b2 = h1->m_pEdge->b;
			c2 = h1->m_pEdge->c;
//			ASSERT(FP_NE(b2*a1, b1*a2));
			if (FP_EQ(a1*b2, a2*b1)) return NULL;
			v0.x = (b2*c1 - b1*c2)/(a1*b2 - a2*b1);
			v0.y = (a2*c1 - a1*c2)/(a2*b1 - a1*b2);
			v0 = v0 - pEdge->m_initPos;
			v0.Normalize();
			if (v0.x*vec.x + v0.y*vec.y < 0.0f)
			{
				pEvent = GetCircleEvent(h0, h1, h2, ypos);
			}
		}
	}
	return pEvent;
}

CCircleEvent* EdgeList::GetCircleEvent(HalfEdge* pHEdge1, HalfEdge* pHEdge2, HalfEdge* pHEdge3, float ypos)
{
	float radius;
	float yvalue;
	Vector center, *p1, *p2, *p3;
	CCircleEvent* pEvent = NULL;

	p1 = &pHEdge1->m_pSite->m_pos;
	p2 = &pHEdge2->m_pSite->m_pos;
	p3 = &pHEdge3->m_pSite->m_pos;

	if (GetCircleFromThreePoints(&center, &radius, p1, p2, p3) == FALSE)
	{
		return NULL;
	}

	yvalue = center.y + radius;
	if (yvalue > ypos)
	{
		pEvent = new CCircleEvent(center, yvalue);
 		pEvent->m_pHEdge[0] = pHEdge1;
		pEvent->m_pHEdge[1] = pHEdge2;
		pEvent->m_pHEdge[2] = pHEdge3;

		Edge* pEdge;
		pEdge = pEvent->m_pHEdge[0]->m_pEdge;
		CCircleEvent** ppEvent1 = (center.x > pEdge->m_initPos.x) ? &pEdge->m_pREvent : &pEdge->m_pLEvent;

		pEdge = pEvent->m_pHEdge[1]->m_pEdge;
		CCircleEvent** ppEvent2 = (center.x > pEdge->m_initPos.x) ? &pEdge->m_pREvent : &pEdge->m_pLEvent;

		if (((*ppEvent1 != NULL) && ((*ppEvent1)->m_yvalue < yvalue)) || ((*ppEvent2 != NULL) && ((*ppEvent2)->m_yvalue < yvalue)))
		{
			SAFE_DELETE(pEvent);
		}
		else
		{
			if (*ppEvent1 != NULL)
			{
				m_pVoronoi->RemoveCircleEvent(*ppEvent1);
			}
			if (*ppEvent2 != NULL)
			{
				m_pVoronoi->RemoveCircleEvent(*ppEvent2);
			}
			*ppEvent1 = pEvent;
			*ppEvent2 = pEvent;
		}
		pHEdge2->m_pEvent = pEvent;
	}
	return pEvent;
}

HalfEdge* EdgeList::Insert(HalfEdge *leftBound, HalfEdge *newHEdge)
{
	if (leftBound == NULL)
	{
		// Add in front of whole list
		newHEdge->m_pLeft = NULL;
		newHEdge->m_pRight = m_pLeftEnd;
		if (m_pLeftEnd == NULL)
		{
			m_pRightEnd = newHEdge;
			
		}
		else
		{
			m_pLeftEnd->m_pLeft = newHEdge;
		}
		m_pLeftEnd = newHEdge;
		leftBound = NULL;
	}
	else
	{
		newHEdge->m_pLeft = leftBound;
		newHEdge->m_pRight = leftBound->m_pRight;
		if (leftBound == m_pRightEnd)
		{
			m_pRightEnd = newHEdge;
		}
		else
		{
			leftBound->m_pRight->m_pLeft = newHEdge;
		}
		leftBound->m_pRight = newHEdge;
	}

	m_nEdgeCount++;
	return leftBound;
}

void EdgeList::Delete(HalfEdge *pHEdge)
{
	CCircleEvent* pEvent;
	if ((pEvent = pHEdge->m_pEvent) != NULL)
	{
		pEvent->m_pHEdge[1] = NULL;
	}
	if ((pHEdge->m_pLeft != NULL) && ((pEvent = pHEdge->m_pLeft->m_pEvent) != NULL))
	{
		pEvent->m_pHEdge[2] = NULL;
	}
	if ((pHEdge->m_pRight != NULL) && ((pEvent = pHEdge->m_pRight->m_pEvent) != NULL))
	{
		pEvent->m_pHEdge[0] = NULL;
	}

	if (pHEdge == m_pLeftEnd)
	{
		if (pHEdge == m_pRightEnd)
		{
			m_pLeftEnd = NULL;
			m_pRightEnd = NULL;
		}
		else
		{
			m_pLeftEnd = pHEdge->m_pRight;
			m_pLeftEnd->m_pLeft = NULL;
		}
	}
	else
	{
		pHEdge->m_pLeft->m_pRight = pHEdge->m_pRight;
		if (pHEdge != m_pRightEnd)
		{
			pHEdge->m_pRight->m_pLeft = pHEdge->m_pLeft;
		}
	}

	m_nEdgeCount--;
	SAFE_DELETE(pHEdge);
}

void EdgeList::InitEdgeList(HalfEdge *newHEdge)
{
	newHEdge->m_pLeft = NULL;
	newHEdge->m_pRight = NULL;
	m_pLeftEnd = newHEdge;
	m_pRightEnd = newHEdge;
	m_nEdgeCount = 1;
}

void EdgeList::RemoveNext(HalfEdge *pNext)
{
	if (pNext->m_pRight != NULL)
		RemoveNext(pNext->m_pRight);
	SAFE_DELETE(pNext);
}

BOOL EdgeList::GetCircleFromThreePoints(Vector* pc, float* radius, Vector* p1, Vector* p2, Vector* p3)
{
	float xa, ya, xb, yb, xayb, yaxb;

	xa = p2->x - p1->x;
	ya = p2->y - p1->y;
	xb = p3->x - p2->x;
	yb = p3->y - p2->y;

	xayb = xa*yb;
	yaxb = ya*xb;

//	ASSERT(FP_NE(xayb, yaxb));
	if (FP_EQ(xayb, yaxb)) return FALSE;
	pc->x = 0.5f * ((p1->x + p2->x)*xayb - (p2->x + p3->x)*yaxb + (p1->y - p3->y)*ya*yb) / (xayb - yaxb);
	pc->y = 0.5f * ((p1->y + p2->y)*yaxb - (p2->y + p3->y)*xayb + (p1->x - p3->x)*xa*xb) / (yaxb - xayb);
	*radius = sqrtf((pc->x - p1->x)*(pc->x - p1->x) + (pc->y - p1->y)*(pc->y - p1->y));

	return TRUE;
}

BOOL EdgeList::GetCircleFromTwoPointsAndTangent(Vector* pc, float* radius, Vector* p1, Vector* p2, float y0, BOOL bSide)
{
	if (FP_EQ(p1->y, p2->y))
	{
		if (FP_EQ(p1->y, y0)) return FALSE;
		else
		{
			pc->x = 0.5f*(p1->x + p2->x);
			pc->y = 0.25f*(p1->x - p2->x)*(p1->x - p2->x)/(p1->y - y0) + 0.5f*(p1->y + y0);
			*radius = fabsf(pc->y - y0);
		}
	}
	else
	{
		float a, mb2, c, sqrtv;
		float y1, y2;
		y1 = p1->y - y0;
		y2 = p2->y - y0;

		a = p2->y - p1->y;
		mb2 = p1->x * y2 - p2->x * y1;
		c = p1->x * p1->x * y2 - p2->x * p2->x * y1 + (p1->y - p2->y) * y1 * y2;
		sqrtv = sqrtf(mb2*mb2 - a*c);
		
		if (bSide == LEFTSIDE)
		{
			pc->x = (mb2 - sqrtv) / a;
		}
		else
		{
			pc->x = (mb2 + sqrtv) / a;
		}
		pc->y = 0.5f*((pc->x - p2->x)*(pc->x - p2->x)/(p2->y - y0) + p2->y + y0);
		*radius = fabsf(pc->y - y0);
	}

	return TRUE;
}