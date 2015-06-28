// EventHeap.cpp: implementation of the CEventHeap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VoronoiTest.h"
#include "EdgeList.h"
#include "EventHeap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventHeap::CEventHeap(CVoronoi* pVoronoi)
{
	m_pHead = NULL;
	m_nEventCount = 0;
}

CEventHeap::~CEventHeap()
{
	m_nEventCount = 0;
}

void CEventHeap::AddNewEvent(CEvent *pNewEvent, BOOL bSort)
{
	if (pNewEvent == NULL) return;
	pNewEvent->m_pNext = NULL;

	if (m_pHead == NULL)
	{
		m_pHead = pNewEvent;
	}
	else if (!bSort || (m_pHead->m_yvalue > pNewEvent->m_yvalue))
	{
		pNewEvent->m_pNext = m_pHead;
		m_pHead = pNewEvent;
	}
	else
	{
		CEvent* pEvent = m_pHead;
		while (pEvent->m_pNext != NULL && pEvent->m_pNext->m_yvalue < pNewEvent->m_yvalue)
		{
			pEvent = pEvent->m_pNext;
		}
		pNewEvent->m_pNext = pEvent->m_pNext;
		pEvent->m_pNext = pNewEvent;
	}

	m_nEventCount++;
}

void CEventHeap::RemoveCircleEvent(CCircleEvent* pEvent)
{
	if (m_pHead == NULL) return;
	if (pEvent == m_pHead)
	{
		m_pHead = m_pHead->m_pNext;
	}
	else
	{
		CEvent* pNext = m_pHead;
		while (pNext->m_pNext != NULL && pNext->m_pNext != pEvent)
		{
			pNext = pNext->m_pNext;
		}
		if (pNext->m_pNext != NULL)
		{
			pNext->m_pNext = pEvent->m_pNext;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		ASSERT(pEvent->m_pHEdge[i] != NULL);
		Edge* pEdge = pEvent->m_pHEdge[i]->m_pEdge;
		if (pEdge->m_pREvent == pEvent)
		{
			pEdge->m_pREvent = NULL;
		}
		if (pEdge->m_pLEvent == pEvent)
		{
			pEdge->m_pLEvent = NULL;
		}
	}
	pEvent->m_pHEdge[1]->m_pEvent = NULL;
	m_nEventCount--;
	delete pEvent;
}

CEvent* CEventHeap::GetNextEvent()
{
	if (m_pHead == NULL)
	{
		return NULL;
	}

	CEvent* pEvent = m_pHead;
	m_pHead = pEvent->m_pNext;
	pEvent->m_pNext = NULL;
	m_nEventCount--;

	return pEvent;
}
