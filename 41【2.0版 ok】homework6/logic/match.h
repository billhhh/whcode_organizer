#ifndef MATCH
#define  MATCH

typedef struct Match
{
	int m;								//P的起始下标
	int n;								//T的起始下标
	int len;								//长度
	Match(int p = 0, int q = 0, int r = 0) : m(p), n(q), len(r)	{}	//只能以三个 int 值构造对象
	~Match() {}
}Match;

#endif	//MATCH