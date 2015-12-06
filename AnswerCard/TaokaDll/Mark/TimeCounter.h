#pragma once
#include <tchar.h>
#include <windows.h>
class TimeCounter
{
protected:
	LARGE_INTEGER start;
	LARGE_INTEGER freq;
public:
	TimeCounter(void);
	~TimeCounter(void);

	void Start() { QueryPerformanceCounter(&start); }
	__int64 Now() //  return miliseconds
	{ 
		LARGE_INTEGER end = { 0 };
		QueryPerformanceCounter(&end);
		return (end.QuadPart - start.QuadPart)*1000 / freq.QuadPart;
	}
	
};

