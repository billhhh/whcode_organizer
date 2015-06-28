#include "Hash.h"


unsigned long time33(const string &str)
{
	const char *temp = str.c_str();
	int len = str.length();
	unsigned long  hash = 0;
	for (int i = 0; i < len; i++)
	{
		hash = ((hash <<5) + hash) + (unsigned long) temp[i];
	}
	return hash;
}

void MyHash::initial_hash()
{
	for (unsigned i = 0; i < HASH_SIZE; ++i)
	{
		lists[i] = new LinkNode;
		lists[i]->data = "";
		lists[i]->num = 0;
	}
}


LinkNode* MyHash::search_hash(const string &str)
{
    unsigned index = (time33(str)) % HASH_SIZE;
    LinkNode *p = lists[index]->next;
    while(p)
    {
        if(p->data == str)
            return p;
        else
            p = p->next;
    }
    return NULL;
}

void MyHash::insert_hash(const string str, int n)
{
    unsigned index = (time33(str)) % HASH_SIZE;
    LinkNode *p = lists[index];
    LinkNode *q = new LinkNode(str, n);

    q->next = p->next;							///ͷ�巨
	p->next = q;
	++ hs_size;
}
