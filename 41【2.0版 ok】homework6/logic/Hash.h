#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include <string>
using namespace std;
const int HASH_SIZE = 1024;
struct LinkNode
{
    string data;
	int num;
    LinkNode *next;
    LinkNode(const string str = "", int n = 0) : data(str), num(n), next(NULL) {}
};

class MyHash
{
public:
    MyHash()
    {
        hs_size = 0;
        for(int i = 0; i < HASH_SIZE; ++i)
            lists[i] = NULL;
    }
    ~MyHash()
    {
		for(unsigned i = 0; i < HASH_SIZE; ++i)
		{
			LinkNode *p = lists[i];
			while(p->next)
			{
				LinkNode *q = p->next;
				p->next = q->next;
				delete q;
			}
			delete p;
		}
    }
	void initial_hash();
    LinkNode* search_hash(const string &temp);
    void insert_hash(const string str, int);
private:
    int hs_size;
    LinkNode *lists[HASH_SIZE];
};

#endif // HASH_H_INCLUDED
