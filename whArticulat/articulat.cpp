#include<stdio.h>
#include<string.h>

#define MAXN 110

bool map[MAXN][MAXN];

int dfn[MAXN],low[MAXN],n,sonTree;
bool visit[MAXN],recrd[MAXN];

inline int get_min(int x,int y){	return x<y?x:y;  }

void init()
{
	memset(map,0,sizeof(map));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(visit,0,sizeof(visit));
	memset(recrd,0,sizeof(recrd));

	sonTree=0;
}

void findArticulat(int u,int depth)
{
	dfn[u]=low[u]=depth; //开始将dfn和low都赋值为当前深度
	visit[u]=1;

	int i;
	for(i=1;i<=n;i++) //为了方便，下标从1开始计数
	{
		if(map[u][i]) //如果u，i有连线
		{
			if(!visit[i]) //且如果 i 没有被访问，就一直深搜下去
			{
				findArticulat(i,depth+1);//继续递归

				low[u]=get_min(low[u],low[i]);

				if(u!=1&&low[i]>=dfn[u]) //如果low[i]>=dfn[u]，代表没有子树可以回边上去
					recrd[u]=1; //标记为关节点

				else if(u==1)//如果u是树根，又有子树没有被访问，子树数量加1
					sonTree++;
			}

			//如果i被访问了，证明有回边，直接更新
			else
				low[u]=get_min(low[u],dfn[i]);
		}
	}
}

int main()
{
	//初始化
	init();

	//输入
	printf("请输入处理点个数：\n");
	scanf("%d",&n);

	printf("请输入处理点连线，输入0结束：\n");

	int i;
	int u,v;
	while(scanf("%d",&u)&&u!=0)
	{
		while(getchar()!='\n')
		{
			scanf("%d",&v);
			map[u][v]=map[v][u]=1;//双向图
		}
	}
	//输入结束

	//处理
	findArticulat(1,1);

	printf("\n");

	//输出
	int count=0;
	if(sonTree>=2)
	{
		count++;
	}
	for(i=2;i<=n;i++)
	{
		if(recrd[i])
		{
			printf("%d是关节点  ",i);
			count++;
		}
	}
	printf("\n一共有关节点数：%d\n",count);


	return 0;
}
