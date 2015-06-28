//暴力法
//构造的超级三角形就是直角三角形
//A(250.0,750.0) B(-500.0,0) C(1000.0,0)

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "mex.h"


/**********定义结构体***********/
typedef struct
{
	double x;
	double y;
}Point;

typedef struct
{
	//存放边的始点和终点下标
	int Start,End;

	//存放边两边的三角形下标
	int Left;
	int Right;
}Edge;


typedef struct
{
	//三角形的三个顶点
	//这里存放的是point数组的下标
	int A,B,C;

	//三角形外心坐标
	Point Center;

	double radius;//外接圆半径

	bool isValid;//判断是不是有效的
}Triangle;



/**********定义全局变量***********/
const int MAXN=6000;
Triangle triangle[MAXN];  //每增加一个点增加3个三角形
Point point[200];

int pCnt=0;//记录输入点数
int triCnt=0;//现有三角形个数

//【新】
int tmpAffTri[MAXN];  //当前受影响的三角形下标
int affectedTriCnt=0;   //当前受影响的三角形的数目
int affEdgeStart[MAXN];//受影响的三角形始点
int affEdgeEnd[MAXN];  //受影响的三角形终点

int outTri[MAXN];  //最后输出的三角形下标
int outTriCnt=0;   //输出Delaunay三角形的个数

Edge edge[MAXN];  //最后找链接外心用到的边数组
int edgeCnt=0;	//控制最后边数输入



/**********定义函数***********/
void init();
double distance(Point A,Point B);
void   miniCircle(Point *p,Point&   center,double&   radius);
void freshTri(int sub);
bool isAffected(int n,int i);
void storeAffEdge(int n);
void pointProcess(int n);
void storeNewTri(int n);         //存入所有新三角形
void offSupTri();
void initEdge();
void findEdgeTri();


//打印点信息
void printPointInfo(Point p)
{
	//mexmexPrintf("****************点  信息********************\n");
	mexPrintf("%.2lf %.2lf\n",p.x,p.y);
	//mexmexPrintf("****************点  信息 END****************\n\n");
}

void printEdgeInfo(Edge e)
{
	//输出边e的信息
	printf("点%d->点%d  Left == %d  Right == %d\n",e.Start,e.End,e.Left,e.Right);
}



//如果说黑盒
//输入：点集坐标    输出：所有外心坐标
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	//接口函数声明  plhs[]是输出指针     prhs[]是输入指针 注意顺序

	//定义三个C的指针变量
	double *num,*x,*y,*y1,*y2,*y3;	//x是输入  y是输出

	num = mxGetPr(prhs[0]);  //获取第一输入参数指针，赋给num
	x = mxGetPr(prhs[1]);     //获取第二个输入参数指针，赋给x

	int pn=num[0];       //进行接口参数的赋值，将输入的第一参数赋给c文件的变量n定义节点的个数
	pCnt=pn;




	//freopen("input.txt","r",stdin);

	//初始化函数，构造超级三角形
	init();

	if(triCnt==0 || pCnt==0)
	{
		//初始化不成功
		mexPrintf("程序初始化失败!!\n");
		return;
	}

	else
		mexPrintf("程序初始化成功...\n");



	mexPrintf("请依次输入处理点坐标：\n");
	//输入点，放入p[]数组，下标0,1,2的点是超级三角形的顶点
	int i;
	Point tmp[MAXN];
	//输入点，放入p[]数组
	for(i=0;i<pn;i++)
	{
		tmp[i].x=x[i];
		tmp[i].y=x[i+pn];
	}
	for(i=3;i<pCnt;i++)
		point[i]=tmp[i-3];

	//test 输出点信息
	for(i=0;i<pCnt;i++)
		printPointInfo(point[i]);


	/*for(i=3;i<pCnt;i++)
		scanf("%lf%lf",&point[i].x,&point[i].y);*/


	//处理
	//对每一个输入点按输入顺序处理
	for(i=3;i<pCnt;i++)
		pointProcess(i);

	offSupTri();

	//输出
	outTriCnt=0;
	mexPrintf("\n三角形外心坐标为：\n");
	//全部处理完毕以后输出所有三角形外心
	for(i=0;i<triCnt;i++)
	{
		//与超级三角形无关的才输出
		if(triangle[i].isValid != false)
		{
			outTri[outTriCnt]=i;
			mexPrintf("(%.2lf,%.2lf)\n",triangle[i].Center.x,triangle[i].Center.y);
			outTriCnt++;
		}
	}

	mexPrintf("outTriCnt == %d\n",outTriCnt);
	mexPrintf("triCnt == %d\n",triCnt);

	plhs[0] = mxCreateDoubleMatrix(outTriCnt*3*2, 1, mxREAL); //创建一个(n-1)×2的矩阵并将矩阵第一个元素所在的位置指针赋给输出参数
	y = mxGetPr(plhs[0]); //获取第一个输出指针，赋给y
	plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
	y1 = mxGetPr(plhs[1]);  //获取第二个输出指针，赋给y1

	for(i=0;i<outTriCnt;i++)
	{
		// y[] 放的就是那两个点【下标】应该连线

		// AB连线
		y[i*6]=triangle[outTri[i]].A-2;
		y[i*6+1]=triangle[outTri[i]].B-2;

		// BC连线
		y[i*6+2]=triangle[outTri[i]].B-2;
		y[i*6+3]=triangle[outTri[i]].C-2;

		// AC连线
		y[i*6+4]=triangle[outTri[i]].A-2;
		y[i*6+5]=triangle[outTri[i]].C-2;

		//test
		printf("画出 %d 号三角形:",outTri[i]);
		mexPrintf("AB:%d->%d   ",triangle[outTri[i]].A-3,triangle[outTri[i]].B-3);
		mexPrintf("BC:%d->%d   ",triangle[outTri[i]].B-3,triangle[outTri[i]].C-3);
		mexPrintf("AC:%d->%d\n",triangle[outTri[i]].A-3,triangle[outTri[i]].C-3);

		
	}

	//为连接外心 初始化边数组
	initEdge();

	findEdgeTri();

	y1[0]=outTriCnt;


	printf("\n");
	//输出测试外心连接      ok
	for(i=0;i<edgeCnt;i++)
	{
		printf("第 %d 条边：",i+1);
		printEdgeInfo(edge[i]);
	}




	//最后的赋值到matlab那边了
	plhs[2] = mxCreateDoubleMatrix(edgeCnt*2*2, 1, mxREAL); //创建一个(n-1)×2的矩阵并将矩阵第一个元素所在的位置指针赋给输出参数
	y2 = mxGetPr(plhs[2]);  //获取第3个输出指针，赋给y2

	plhs[3] = mxCreateDoubleMatrix(1, 1, mxREAL);
	y3 = mxGetPr(plhs[3]);  //获取第4个输出指针，赋给y3
	y3[0]=edgeCnt;

	for(i=0;i<edgeCnt;i++)
	{
		y2[i*4]=triangle[edge[i].Left].Center.x;
		y2[i*4+1]=triangle[edge[i].Left].Center.y;

		if(edge[i].Right==-1)
		{
			y2[i*4+2]=( point[edge[i].Start].x + point[edge[i].End].x )/2;
			y2[i*4+3]=( point[edge[i].Start].y + point[edge[i].End].y )/2;
		}

		else
		{
			y2[i*4+2]=triangle[edge[i].Right].Center.x;
			y2[i*4+3]=triangle[edge[i].Right].Center.y;
		}
	}

}








void findEdgeTri()
{
	//找最后的边两边的三角形
	int i,j;
	int edgeCnt_ori;

	for(i=0;i<outTriCnt;i++)
	{
		//【第i个】三角形     【第j条】边
		edgeCnt_ori=edgeCnt;

		//  AB边
		for(j=0;j<edgeCnt_ori;j++)
		{
			if(  (triangle[outTri[i]].A == edge[j].Start && triangle[outTri[i]].B == edge[j].End) || (triangle[outTri[i]].B == edge[j].Start && triangle[outTri[i]].A == edge[j].End)  )
			{
				//发现重边，把边的Right指向该三角形
				edge[j].Right=outTri[i];
				break;
			}
		}

		if(j==edgeCnt_ori)
		{
			//正常退出循环，直接加入该边
			edge[edgeCnt].Start=triangle[outTri[i]].A;
			edge[edgeCnt].End=triangle[outTri[i]].B;

			edge[edgeCnt].Left=outTri[i];    //自己复制给Left

			edgeCnt++;
		}



		//  BC边
		for(j=0;j<edgeCnt_ori;j++)
		{
			if(  (triangle[outTri[i]].B == edge[j].Start && triangle[outTri[i]].C == edge[j].End) || (triangle[outTri[i]].C == edge[j].Start && triangle[outTri[i]].B == edge[j].End)  )
			{
				//发现重边，把边的Right指向该三角形
				edge[j].Right=outTri[i];
				break;
			}
		}

		if(j==edgeCnt_ori)
		{
			//正常退出循环，直接加入该边
			edge[edgeCnt].Start=triangle[outTri[i]].B;
			edge[edgeCnt].End=triangle[outTri[i]].C;

			edge[edgeCnt].Left=outTri[i];

			edgeCnt++;
		}


		//  AC边
		for(j=0;j<edgeCnt_ori;j++)
		{
			if(  (triangle[outTri[i]].A == edge[j].Start && triangle[outTri[i]].C == edge[j].End) || (triangle[outTri[i]].C == edge[j].Start && triangle[outTri[i]].A == edge[j].End)  )
			{
				//发现重边，把边的Right指向该三角形
				edge[j].Right=outTri[i];
				break;
			}
		}

		if(j==edgeCnt_ori)
		{
			//正常退出循环，直接加入该边
			edge[edgeCnt].Start=triangle[outTri[i]].A;
			edge[edgeCnt].End=triangle[outTri[i]].C;

			edge[edgeCnt].Left=outTri[i];

			edgeCnt++;
		}


	}
}



void initEdge()
{
	edgeCnt=0;

	int i;
	for(i=0;i<MAXN;i++)
	{
		edge[i].Left=-1;
		edge[i].Right=-1;
	}
}



void offSupTri()
{
	//去掉超级三角形
	int i;
	for(i=0;i<triCnt;i++)
	{
		if(triangle[i].A==0 || triangle[i].B==0 || triangle[i].C==0)
			triangle[i].isValid=false;

		else if(triangle[i].A==1 || triangle[i].B==1 || triangle[i].C==1)
			triangle[i].isValid=false;

		else if(triangle[i].A==2 || triangle[i].B==2 || triangle[i].C==2)
			triangle[i].isValid=false;
	}
}



//初始化函数，构造超级三角形
void init()
{
	//初始化所有三角形，isValid 为 true
	//开始初始化都为有效
	int i;
	for(i=0;i<MAXN;i++)
		triangle[i].isValid=true;

	point[0].x=250.0;
	point[0].y=750.0;

	point[1].x=-500.0;
	point[1].y=0;

	point[2].x=1000.0;
	point[2].y=0;

	//0下标的是超级三角形
	triangle[0].A=0;
	triangle[0].B=1;
	triangle[0].C=2;

	triangle[0].Center.x=250.0;
	triangle[0].Center.y=0;

	triangle[0].radius=750.0;   //707.10678118654752440084436210485

	triCnt=1;

	//mexPrintf("一共处理点数目：\n");
	//scanf("%d",&pCnt);
	pCnt+=3;
}



double distance(Point A,Point B)
{
	double dis = (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);

	return sqrt(dis);
}



void   miniCircle(Point *p,Point&   center,double&   radius)
{
	double   Xmove=p[0].x;   
	double   Ymove=p[0].y;
	p[1].x=p[1].x-p[0].x;
	p[1].y=p[1].y-p[0].y;
	p[2].x=p[2].x-p[0].x;
	p[2].y=p[2].y-p[0].y;
	p[0].x=0;
	p[0].y=0;
	int  index;

	double   x1=p[1].x,y1=p[1].y,x2=p[2].x,y2=p[2].y;   
	double   m=2.0*(x1*y2-y1*x2);   
	center.x=(x1*x1*y2-x2*x2*y1+y1*y2*(y1-y2))/m;   
	center.y=(x1*x2*(x2-x1)-y1*y1*x2+x1*y2*y2)/m;   
	radius=distance(center,p[0]);
	center.x+=Xmove;   
	center.y+=Ymove;     

}


//更新三角形 外心、半径
void freshTri(int sub)
{
	Point p[3];

	//更新三角形的下标为sub
	p[0]=point[triangle[sub].A];
	p[1]=point[triangle[sub].B];
	p[2]=point[triangle[sub].C];

	miniCircle(p,triangle[sub].Center,triangle[sub].radius);

}


//判断三角形是否受影响的函数
//判断第 n 点和第 i 个三角形
bool isAffected(int n,int i)
{
	double dis = distance(point[n],triangle[i].Center);

	if(dis<triangle[i].radius)
		return true;

	else
		return false;
}


void storeAffEdge(int n)
{
	//存入 第n个 三角形的三边
	int i;
	int a=triangle[n].A;
	int b=triangle[n].B;
	int c=triangle[n].C;

	for(i=0;i<affectedTriCnt*3;i++)
	{
		if((a == affEdgeStart[i] && b == affEdgeEnd[i]) || (b == affEdgeStart[i] && a == affEdgeEnd[i]))
		{
			//AB重边
			affEdgeStart[i]=-1;
			affEdgeEnd[i]=-1;

			affEdgeStart[(affectedTriCnt-1)*3]=-1;
			affEdgeEnd[(affectedTriCnt-1)*3]=-1;

			break;
		}
	}

	if(i==affectedTriCnt*3)
	{
		affEdgeStart[(affectedTriCnt-1)*3]=a;
		affEdgeEnd[(affectedTriCnt-1)*3]=b;
	}

	for(i=0;i<affectedTriCnt*3;i++)
	{
		if((b == affEdgeStart[i] && c == affEdgeEnd[i]) || (c == affEdgeStart[i] && b == affEdgeEnd[i]))
		{
			//BC重边
			affEdgeStart[i]=-1;
			affEdgeEnd[i]=-1;

			affEdgeStart[(affectedTriCnt-1)*3+1]=-1;
			affEdgeEnd[(affectedTriCnt-1)*3+1]=-1;

			break;
		}
	}

	if(i==affectedTriCnt*3)
	{
		affEdgeStart[(affectedTriCnt-1)*3+1]=b;
		affEdgeEnd[(affectedTriCnt-1)*3+1]=c;
	}




	for(i=0;i<affectedTriCnt*3;i++)
	{
		if((a == affEdgeStart[i] && c == affEdgeEnd[i]) || (c == affEdgeStart[i] && a == affEdgeEnd[i]))
		{
			//AC重边
			affEdgeStart[i]=-1;
			affEdgeEnd[i]=-1;

			affEdgeStart[(affectedTriCnt-1)*3+2]=-1;
			affEdgeEnd[(affectedTriCnt-1)*3+2]=-1;

			break;
		}
	}

	if(i==affectedTriCnt*3)
	{
		affEdgeStart[(affectedTriCnt-1)*3+2]=a;
		affEdgeEnd[(affectedTriCnt-1)*3+2]=c;
	}

}


void storeNewTri(int n)
{
	//新加入点是下标为n的点
	int i;
	for(i=0;i<affectedTriCnt*3;i++)
	{
		if(affEdgeStart[i]==-1)
			continue;

		triangle[triCnt].A=affEdgeStart[i];
		triangle[triCnt].B=affEdgeEnd[i];
		triangle[triCnt].C=n;

		freshTri(triCnt);

		triCnt++;
	}
}


void pointProcess(int n)
{
	//affEdge[] init
	memset(affEdgeStart,-1,sizeof(affEdgeStart));
	memset(affEdgeEnd,-1,sizeof(affEdgeEnd));

	//处理下标为【n】的 point
	//求该点同所有三角形外心的距离，如果距离小于外接圆半径，则为该三角形受影响
	int i;

	int triCnt_ori = triCnt;   //不能让新加入的“影响三角形”影响循环次数



	affectedTriCnt=0;
	for(i=0;i<triCnt_ori;i++)
	{
		//判断该点【第n点】和【第i个】三角形
		if(triangle[i].isValid==true && isAffected(n,i)==true)
		{
			tmpAffTri[affectedTriCnt]=i;  //1、受到影响了，先把所有的影响三角形存入一个待处理的三角形数组
			affectedTriCnt++;
			triangle[i].isValid=false; //之后再加入，先设为无效

			storeAffEdge(i);	//2、将【第i个】三角形的边放入影响边数组，顺便去掉当前影响三角形重边，重边start和end赋值为-1
		}
	}
	storeNewTri(n);     //将【步骤2】的边和新加入的【第n点】组成新三角形，放入triangle数组

}
