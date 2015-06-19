#include "rkr_gst_match.h"
#include "Hash.h"

void RKR_GST_Match::beginMatch(int initialLength)
{
	searchLength = initialLength;
	while(searchLength > minLength)
	{
		lmax = scanPattern(searchLength);
		if (lmax > 2 * searchLength)
		{
			searchLength = lmax;
		} 
		else
		{
			markStrings(searchLength);
			if (searchLength > 2 * minLength)
			{
				searchLength = (int)ceil((double) searchLength / 2);
			} 
			else if (searchLength > minLength)
			{
				searchLength = minLength;
			}
		}
	}
}

int RKR_GST_Match::scanPattern(int s)
{
	int maxLengthOfMatch = -1;
	MyHash hs;
	hs.initial_hash();
	for (int n = 0; n < lenT; ++n)
	{
		if (! bitvecT.test(n))
		{
			int index = getNextTileIndex(bitvecT, n, lenT);			//下一个 tile 的下标
			if (index - n < s)													//到下一个 tile 的距离小于等于 s
			{
				n = moveNextTileIndex(bitvecT, index, lenT);
				continue;
			} 
			else
			{
				string str =strT.substr(n, s);								//建立 strT 的长度为 s 的哈希表
				hs.insert_hash(str, n);
				//hs.insert(pair<string, int>(str,n));
			}
		}
		else
			continue;
	}
	for (int m = 0; m < lenP; ++m)
	{
		if (! bitvecP.test(m))
		{
			int index = getNextTileIndex(bitvecP, m, lenP);		//下一个 tile 的下标
			if (index - m < s)													//到下一个 tile 的距离小于等于 s
			{
				m = moveNextTileIndex(bitvecT, index, lenT);
				continue;
			}
			else
			{
				string str = strP.substr(m, s);
				LinkNode *temp = hs.search_hash(str);
				if (NULL != temp)													
				{
					int n = temp->num;									//哈希表中存在该字符串
					int k = s;
					while(m + k < lenP && n + k < lenT && strP[m + k] == strT[n + k] && (! bitvecP[m + k]) &&(! bitvecT[n + k]))
						++k;
					maxLengthOfMatch = k;
					if (k > 2 * s)												//放弃扫描，从新的 s 开始扫描
					{
						return k;
					} 
					else															//记下新的最大匹配
					{
						Match mat(n, m, k);
						mapQue[k].push(mat);
						maxLengthOfMatch = maxLengthOfMatch > k ? maxLengthOfMatch : k;//记下最大匹配长度
					}
				}			
			}
		}
		else
			continue;
	}
	return maxLengthOfMatch;
}

void RKR_GST_Match::markStrings(int s)
{
	map<int, queue<Match>, greater<int> >::iterator iter = mapQue.begin();
	for ( ; iter != mapQue.end(); iter = mapQue.begin())									//对 map 中的每对 <int, queue<Match> > 进行处理
	{
		const int length = iter->first;
		queue<Match> temp = iter->second;
		mapQue.erase(length);
		while (! temp.empty())										//队列不为空
		{
			Match mat = temp.front();
			temp.pop();
			if (! occlude(mat))													//若没重叠
			{
				mark(bitvecP, mat.m, length, lenP);
				mark(bitvecT, mat.n, length, lenT);
				matches.push_back(mat);
			}
			else
				continue;
		}
	}
}

bool RKR_GST_Match::occlude(Match mat)			//若当前 match 与 matches 里元素有重叠部分，返回 true， 否则返回 false
{
	bool tag = false;
	int m = mat.m;												//取出 mat 三元组的元素
	int n = mat.n;
	int len = mat.len;
	for (int i = 0; i < matches.size(); ++i)
	{
		Match temp = matches[i];							//对 matches 每个元素进行比较
		int p = temp.m;
		int q = temp.n;
		int r = temp.len;
		if ((m < p && m + len > p) || (m > p && m < p + r))
		{
			tag = true;
			return tag;
		}
		if ((n < q && m + len > q) || (n > q && n < q + r))
		{
			tag = true;
			return tag;
		}
	}
	return tag;
}

int RKR_GST_Match::getNextTileIndex(bitset<MAX_LENGTH_TEXT> &bits, int x, int len)
{
	int i = 0;
	bool tag = false;
	for (i = x + 1; i < len ; ++i)
	{
		if (! bits.test(i))
			continue;
		else
		{
			tag = true;
			break;
		}
	}
	if (tag)
		return i;
	return len;
}

int RKR_GST_Match::moveNextTileIndex(bitset<MAX_LENGTH_TEXT> &bits, int x, int len)
{	int i = 0;
	for ( i = x + 1; i < len - 1; ++i)
	{
		if (bits.test(i))
		{
			continue;
		}
		else
			break;
	}
	return i;
}

void RKR_GST_Match::mark(bitset<MAX_LENGTH_TEXT> &bits, int x, int len, int boundary)
{
	for (int i = x; i < x + len  && i < boundary ; ++i)
	{
		bits.set(i);
	}
}