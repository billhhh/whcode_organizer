// EventHeap.h: interface for the CEventHeap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTHEAP_H__3FE1C195_CE39_11D5_83A3_000347397404__INCLUDED_)
#define AFX_EVENTHEAP_H__3FE1C195_CE39_11D5_83A3_000347397404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Event.h"

class CVoronoi;
class CEventHeap  
{
public:
	CEventHeap(CVoronoi* pVoronoi);
	virtual ~CEventHeap();

public:
	BOOL	IsEmpty() { return m_pHead == NULL; };
	void	RemoveCircleEvent(CCircleEvent* pEvent);
	void	AddNewEvent(CEvent* pNewEvent, BOOL bSort = FALSE);
	void	GetNextEventValue(float& eventval) { eventval = m_pHead->m_yvalue; };
	CEvent* GetNextEvent();
	CEvent* GetHeadPointer() { return m_pHead; };
	CEvent* GetNextEventPointer(CEvent* pEvent) { return pEvent->m_pNext; };

private:
	int			m_nEventCount;
	CEvent*		m_pHead;
};

#endif // !defined(AFX_EVENTHEAP_H__3FE1C195_CE39_11D5_83A3_000347397404__INCLUDED_)
