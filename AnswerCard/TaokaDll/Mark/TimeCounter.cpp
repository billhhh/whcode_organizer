#include "StdAfx.h"
#include "TimeCounter.h"


TimeCounter::TimeCounter(void)
{ 
	QueryPerformanceFrequency(&freq);
	Start();
}


TimeCounter::~TimeCounter(void)
{
}
