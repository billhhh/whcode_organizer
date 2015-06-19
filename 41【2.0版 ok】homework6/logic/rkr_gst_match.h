#include "match.h"
#include <math.h>
#include <hash_map>
#include <string>
#include <queue>
#include <vector>
#include <bitset>
#include <map>

const int MAX_LENGTH_TEXT = 100000;

using namespace std;
class RKR_GST_Match
{
private:
	string strT;													//文本串
	string strP;													//模式串
	int lenT;
	int lenP;
	bitset<MAX_LENGTH_TEXT> bitvecT;				//文本串的mark
	bitset<MAX_LENGTH_TEXT> bitvecP;				//模式串的mark
public:
	vector <Match> matches;							//P 、T 的匹配结果
private:
	int minLength;												//最小公共子串长度
	int searchLength;											//搜索长度
	int lmax;														//循环中找到的最大的最大匹配大小
	map<int, queue<Match>, greater<int> > mapQue;							//记录最大匹配
public:
	RKR_GST_Match(string &t, string &p, int len)
		: strT(t), strP(p)	, minLength(len),	searchLength (0), lmax (0)			//只能以两个string构造该类对象
	{
		lenP = strP.length();
		lenT = strT.length();
		bitvecT.reset();
		bitvecP.reset();
	}
	~RKR_GST_Match() {}
	void beginMatch(int initialLength);
	int scanPattern(int s);																	//扫描模式
	void markStrings(int s);																	//处理最大匹配
	bool occlude(Match m);																	//当前Match是否重叠
	int getNextTileIndex(bitset<MAX_LENGTH_TEXT> &bits, int , int);
	int moveNextTileIndex(bitset<MAX_LENGTH_TEXT> &bits, int , int);
	void mark(bitset<MAX_LENGTH_TEXT> &bits, int x, int len, int boundary);
};
