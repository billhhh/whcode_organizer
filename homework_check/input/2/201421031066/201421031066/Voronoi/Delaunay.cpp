// File: Delaunay.cpp
// Description: Delaunay class to triangluate points set in 2D. 
// TODO: The procedure uses Double List for holding data, it can be optimized by using another data structure such as DAG, Quad-edge, etc.
// Author: sunlin
// Date: 21/9/2014
//

// INCLUDES ///////////////////////////////////////////////
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "windows.h" // for time statistics

// DEFINES ////////////////////////////////////////////////
#define MAX_VERTEX_NUM 4092

#ifdef SINGLE
#define REAL float
#else
#define REAL double
#endif


typedef struct VERTEX2D_TYP
{
    REAL x;
    REAL y;

} VERTEX2D, *VERTEX2D_PTR;

typedef struct EDGE_TYP
{
    VERTEX2D v1;
    VERTEX2D v2;
    EDGE_TYP* pNext;

} EDGE, *EDGE_PTR;

typedef struct TRIANGLE_TYP
{
    int i1; // vertex index
    int i2;
    int i3;

    VERTEX2D center;
    TRIANGLE_TYP* pNext;
    TRIANGLE_TYP* pPrev;

} TRIANGLE, *TRIANGLE_PTR;

typedef struct MESH_TYP
{
    int vertex_num;
    int triangle_num;

    VERTEX2D_PTR pVerArr; // point to outer vertices arrary
    TRIANGLE_PTR pTriArr; // point to outer triangles arrary
    EDGE_PTR pEdgeArr; // point to voronoi edges arrary

} MESH, *MESH_PTR;

typedef struct VERTEX_TYP
{

    int value;
    int ID;
    VERTEX2D_PTR vernode;
    TRIANGLE_PTR pTriArr; // point to outer triangles arrary
    VERTEX_TYP* next;

} VERTEX, *VERTEX_PTR;
typedef struct ordertri_TYP
{

    int vertex_num;

    VERTEX_PTR VerArr; // point to outer vertices arrary

} orderVer, *ORDERVER_PTR;


// PROTOTYPES ///////////////////////////////////////////
// Delaunay triangulation functions
void InitMesh(MESH_PTR pMesh, int ver_num);//初始化三角网，完成分配内存和初始化顶点的工作
void UnInitMesh(MESH_PTR pMesh);//释放内存，程序结束时调用 

void AddBoundingBox(MESH_PTR pMesh);//构造超级三角形把所有的点都包含
void RemoveBoundingBox(MESH_PTR pMesh);;//移除超级三角形
void IncrementalDelaunay(MESH_PTR pMesh);//随机增量法构造Delaunay三角网，主函数调用

void Insert(MESH_PTR pMesh, int ver_index);//在原有的Delaunay网上插入点，生成新的三角网
bool FlipTest(MESH_PTR pMesh, TRIANGLE_PTR pTestTri);//插入点后进行的局部调整操作，使新增加的三角形满足Delaunay三角形特性

REAL InCircle(VERTEX2D_PTR pa, VERTEX2D_PTR pb, VERTEX2D_PTR pp, VERTEX2D_PTR  pd);//判断pp是否在由pa、pb，pc组成的三角形的外接圆上
REAL InTriangle(MESH_PTR pMesh, VERTEX2D_PTR pVer, TRIANGLE_PTR pTri);//寻找插入点所在的三角形

void InsertInTriangle(MESH_PTR pMesh, TRIANGLE_PTR pTargetTri, int ver_index);//如果插入点在三角边上的插入操作
void InsertOnEdge(MESH_PTR pMesh, TRIANGLE_PTR pTargetTri, int ver_index);//如果插入点在三角形内的插入操作
void FindEdge(MESH_PTR pMesh);
//void FindEdge(MESH_PTR pMesh);//由Delaunay三角网构造出维诺图

// Helper functions
void RemoveTriangleNode(MESH_PTR pMesh, TRIANGLE_PTR pTri);//从三角链表中删除三角形
TRIANGLE_PTR AddTriangleNode(MESH_PTR pMesh, TRIANGLE_PTR pPrevTri, int i1, int i2, int i3);//从三角链表中插入一个新的三角形

// I/O functions
void Input(char* pFile, MESH_PTR pMesh);
void Output(char* pFile, MESH_PTR pMesh);

// GLOBALS ////////////////////////////////////////////////


// FUNCTIONS //////////////////////////////////////////////
int main(int argc, char** argv)
{
	if(argc!=3)
	{
		fprintf(stderr,"Usage:%s InputFileName OutputFileName\n",argv[0]);
		exit(1);
	}

	MESH mesh;
	double last_time, this_time;
	//int ver_num;
	//int tri_num;

	Input(argv[1], &mesh);

	last_time = GetTickCount();		

	IncrementalDelaunay(&mesh);	//随机增量法构造Delaunay三角网，主函数调用
	//Sleep(1000);
	FindEdge(&mesh);
	this_time = GetTickCount();	

	printf("Elapsed Time for Incremental Delaunay: %lg ms", this_time - last_time);
	
	Output(argv[2], &mesh);

	return 0;
}

// The format of input file should be as follows:
// The First Line: amount of vertices (the amount of vertices/points needed to be triangulated)
// Other Lines: x y z (the vertices/points coordinates, z should be 0 for 2D)
// E.g. 
// 4
// -1 -1 0
// -1 1 0
// 1 1 0
// 1 -1 0
void Input(char* pFile, MESH_PTR pMesh)
{
	FILE* fp = fopen(pFile, "r");

	if (!fp)
	{
		fprintf(stderr,"Error:%s open failed\n", pFile);
		exit(1);
	}

	//int face;
	int amount;

	//fscanf( fp, "%d", &face);
	fscanf( fp, "%d", &amount);
	if (amount < 3)
	{
		fprintf(stderr,"Error:vertex amount should be greater than 2, but it is %d \n",amount);
		exit(1);
	}

	InitMesh(pMesh, amount);

	REAL x,y;
	for ( int j=3; j<amount+3; ++j)   //前三个顶点用来存储超级三角形的三个顶点
	{
		fscanf( fp, "%lg %lg", &x, &y);
		((VERTEX2D_PTR)(pMesh->pVerArr+j))->x = x;
		((VERTEX2D_PTR)(pMesh->pVerArr+j))->y = y;
	}


	fclose(fp);
}

// Algorithm IncrementalDelaunay(V)
// Input: 由n个点组成的二维点集V
// Output: Delaunay三角剖分DT
//	1.add a appropriate triangle boudingbox to contain V ( such as: we can use triangle abc, a=(0, 3M), b=(-3M,-3M), c=(3M, 0), M=Max({|x1|,|x2|,|x3|,...} U {|y1|,|y2|,|y3|,...}))
//	2.initialize DT(a,b,c) as triangle abc
//	3.for i <- 1 to n 
//		do (Insert(DT(a,b,c,v1,v2,...,vi-1), vi))   在原有的Delaunay网上插入点，生成新的三角网
//	4.remove the boundingbox and relative triangle which cotains any vertex of triangle abc from DT(a,b,c,v1,v2,...,vn) and return DT(v1,v2,...,vn).
void IncrementalDelaunay(MESH_PTR pMesh)	//随机增量法构造Delaunay三角网，主函数调用
{
	// Add a appropriate triangle boudingbox to contain V
	AddBoundingBox(pMesh);	//构造超级三角形把所有的点都包含

	// Get a vertex/point vi from V and Insert(vi)
	for (int i=3; i<pMesh->vertex_num+3; i++) //逐个加入V中的点
	{
		Insert(pMesh, i);
	}

	// Remove the bounding box
	RemoveBoundingBox(pMesh);
}

// The format of output file should be as follows:
// triangle index
// x1 y1 (the coordinate of first vertex of triangle)
// x2 y2 (the coordinate of second vertex of triangle)
// x3 y3 (the coordinate of third vertex of triangle)
void Output(char* pFile, MESH_PTR pMesh)
{
FILE* fp = fopen(pFile, "w");
	if (!fp)
	{
		fprintf(stderr,"Error:%s open failed\n", pFile);

		UnInitMesh(pMesh);
		exit(1);
	}

	TRIANGLE_PTR pTri = pMesh->pTriArr;// 指向三角链表
	EDGE_PTR pEdge = pMesh->pEdgeArr;// 指向三角链表
	int* pi;
	int vertex_index;
	int tri_index = 0;
	while(pTri != NULL)	
	{
		fprintf(fp, "Triangle: %d\n", ++tri_index);

		pi = &(pTri->i1);
		for (int j=0; j<3; j++)	
		{	
			vertex_index = *pi++;		
			fprintf(fp, "%lg %lg\n", ((VERTEX2D_PTR)(pMesh->pVerArr+vertex_index))->x, ((VERTEX2D_PTR)(pMesh->pVerArr+vertex_index))->y);
		}

		pTri = pTri->pNext;
	}
	while(pEdge != NULL)	
	{
		fprintf(fp, "Edge: %d\n", ++tri_index);
		
		fprintf(fp, "%lg %lg\n", ((VERTEX2D)pEdge->v1).x, ((VERTEX2D)pEdge->v1).y);
		fprintf(fp, "%lg %lg\n", ((VERTEX2D)pEdge->v2).x, ((VERTEX2D)pEdge->v2).y);

		pEdge = pEdge->pNext;
	}

	fclose(fp);

	UnInitMesh(pMesh);
}


// Allocate memory to store vertices and triangles
void InitMesh(MESH_PTR pMesh, int ver_num )	//初始化三角网，完成分配内存和初始化顶点的工作
{
	// Allocate memory for vertex array
	pMesh->pVerArr = (VERTEX2D_PTR)malloc((ver_num+3)*sizeof(VERTEX2D));	//顶点链表
	pMesh->pEdgeArr = (EDGE_PTR)malloc((ver_num)*sizeof(VERTEX2D));	//顶点链表
	if (pMesh->pVerArr == NULL)
	{
		fprintf(stderr,"Error:Allocate memory for mesh failed\n");
		exit(1);
	}
	pMesh->pEdgeArr->pNext=NULL;
	pMesh->vertex_num = ver_num;	//顶点数

}

// Deallocate memory
void UnInitMesh(MESH_PTR pMesh)				//释放内存，程序结束时调用
{
	// free vertices
	if(pMesh->pVerArr != NULL)
		free(pMesh->pVerArr);

	// free triangles
	TRIANGLE_PTR pTri = pMesh->pTriArr;
	TRIANGLE_PTR pTemp = NULL;
	while (pTri != NULL)
	{
		pTemp = pTri->pNext;
		free(pTri);
		pTri = pTemp;
	}
}

void AddBoundingBox(MESH_PTR pMesh)			//构造超级三角形把所有的点都包含
{
	REAL max = 0;
	REAL max_x = 0;
	REAL max_y = 0;
	REAL t;

	for (int i=3; i<pMesh->vertex_num+3; i++)
	{
		t = abs(((VERTEX2D_PTR)(pMesh->pVerArr+i))->x);//abs求整型数是的绝对值 ，fabs求带小数的绝对值
		if (max_x < t)
		{
			max_x = t;
		}

		t = abs(((VERTEX2D_PTR)(pMesh->pVerArr+i))->y);
		if (max_y < t)
		{
			max_y = t;
		}
	}

	max = max_x > max_y ? max_x:max_y;

	//TRIANGLE box;
	//box.v1 = VERTEX2D(0, 4*max);
	//box.v2 = VERTEX2D(-4*max, 4*max);
	//box.v3 = VERTEX2D(4*max, 0);

	VERTEX2D v1 = {0, 4*max};
	VERTEX2D v2 = {-4*max, -4*max};
	VERTEX2D v3 = {4*max, 0};

	// Assign to Vertex array
	*(pMesh->pVerArr) = v1;
	*(pMesh->pVerArr + 1) = v2;
	*(pMesh->pVerArr + 2) = v3;

	// add the Triangle boundingbox
	AddTriangleNode(pMesh, NULL, 0, 1, 2);
}

void RemoveBoundingBox(MESH_PTR pMesh)		//移除超级三角形
{
	int statify[3]={0,0,0};
	int vertex_index;
	int* pi;
	int k = 1;
	
	// Remove the first triangle-boundingbox
	//pMesh->pTriArr = pMesh->pTriArr->pNext;
	//pMesh->pTriArr->pPrev = NULL; // as head

	TRIANGLE_PTR pTri = pMesh->pTriArr;
	TRIANGLE_PTR pNext = NULL;
	while (pTri != NULL)
	{
		pNext = pTri->pNext;

		statify[0] = 0;
		statify[1] = 0;
		statify[2] = 0;

		pi = &(pTri->i1);
		for (int j=0, k = 1; j<3; j++, k*= 2)
		{			
			vertex_index = *pi++;

			if(vertex_index == 0 || vertex_index == 1 || vertex_index == 2) // bounding box vertex
			{
				statify[j] = k;
			}
		}

		switch(statify[0] | statify[1] | statify[2] )
		{
		case 0: // no statify
			break;
		case 1:
		case 2:
		case 4: // 1 statify, remove 1 triangle, 1 vertex
			RemoveTriangleNode(pMesh, pTri);		
			break;
		case 3:
		case 5:
		case 6: // 2 statify, remove 1 triangle, 2 vertices
			RemoveTriangleNode(pMesh, pTri);			
			break;
		case 7: // 3 statify, remove 1 triangle, 3 vertices
			RemoveTriangleNode(pMesh, pTri);
			break;
		default:
			break;
		}

		// go to next item
		pTri = pNext;
	}
}


// Return a positive value if the points pa, pb, and
// pc occur in counterclockwise order; a negative
// value if they occur in clockwise order; and zero
// if they are collinear. The result is also a rough
// approximation of twice the signed area of the
// triangle defined by the three points.
//counterclockwise：逆时针方向；（返回正数）clockwise：顺时针方向；（返回负数）collinear：共线（返回0）	
REAL CounterClockWise(VERTEX2D_PTR pa, VERTEX2D_PTR pb, VERTEX2D_PTR pc)
{
	return ((pb->x - pa->x)*(pc->y - pb->y) - (pc->x - pb->x)*(pb->y - pa->y));
}

// Adjust if the point lies in the triangle abc
REAL InTriangle(MESH_PTR pMesh, VERTEX2D_PTR pVer, TRIANGLE_PTR pTri)	//寻找插入点所在的三角形
{
	int vertex_index;
	VERTEX2D_PTR pV1, pV2, pV3;

	vertex_index =pTri->i1;
	pV1 = (VERTEX2D_PTR)(pMesh->pVerArr+vertex_index);
	vertex_index =pTri->i2;
	pV2 = (VERTEX2D_PTR)(pMesh->pVerArr+vertex_index);
	vertex_index =pTri->i3;
	pV3 = (VERTEX2D_PTR)(pMesh->pVerArr+vertex_index);

	REAL ccw1 = CounterClockWise(pV1, pV2, pVer);
	REAL ccw2 = CounterClockWise(pV2, pV3, pVer);
	REAL ccw3 = CounterClockWise(pV3, pV1, pVer);

	REAL r = -1;//error
	if (ccw1>0 && ccw2>0 && ccw3>0)	//pVer在pV1、pV2、pV3三角形内部返回1
	{
		r = 1;//pVer在pV1、pV2、pV3三角形内部
	}
	else if(ccw1*ccw2*ccw3 == 0 && (ccw1*ccw2 > 0 || ccw1*ccw3 > 0 || ccw2*ccw3 > 0) )//ccw1*ccw2*ccw3 == 0表示pVer在三角形上
	{																				  //ccw1*ccw2 > 0 || ccw1*ccw3 > 0 || ccw2*ccw3 > 0)表示pVer在三角形外
		r = 0;//pVer在三角形上或三角形外
	}

	return r;
}

// Algorithm Insert(DT(a,b,c,v1,v2,...,vi-1), vi)
// 1.find the triangle vavbvc which contains vi // FindTriangle()
// 2.if (vi located at the interior of vavbvc)  
// 3.    then add triangle vavbvi, vbvcvi and vcvavi into DT // UpdateDT()
// FlipTest(DT, va, vb, vi)
// FlipTest(DT, vb, vc, vi)
// FlipTest(DT, vc, va, vi)
// 4.else if (vi located at one edge (E.g. edge vavb) of vavbvc) 
// 5.    then add triangle vavivc, vivbvc, vavdvi and vivdvb into DT (here, d is the third vertex of triangle which contains edge vavb) // UpdateDT()
// FlipTest(DT, va, vd, vi)
// FlipTest(DT, vc, va, vi)
// FlipTest(DT, vd, vb, vi)
// FlipTest(DT, vb, vc, vi)
// 6.return DT(a,b,c,v1,v2,...,vi)
void Insert(MESH_PTR pMesh, int ver_index)	//在原有的Delaunay网上插入点生生成新的三角网
{
	VERTEX2D_PTR pVer = (VERTEX2D_PTR)(pMesh->pVerArr+ver_index);
	TRIANGLE_PTR pTargetTri = NULL;
	TRIANGLE_PTR pEqualTri1 = NULL;
	TRIANGLE_PTR pEqualTri2 = NULL;

	int j = 0;
	TRIANGLE_PTR pTri = pMesh->pTriArr;
	while (pTri != NULL)
	{
		REAL r = InTriangle(pMesh, pVer, pTri);//寻找插入点所在的三角形
		if(r > 0) // should be in triangle	//在三角形的内部
		{
			pTargetTri = pTri;
		}
		else if (r == 0) // should be on edge	//在三角形的边上
		{
			if(j == 0)
			{
				pEqualTri1 = pTri;
				j++;				
			}
			else
			{
				pEqualTri2 = pTri;
			}
			
		}

		pTri = pTri->pNext;
	}

	if (pEqualTri1 != NULL && pEqualTri2 != NULL)
	{
		InsertOnEdge(pMesh, pEqualTri1, ver_index);
		InsertOnEdge(pMesh, pEqualTri2, ver_index);
	}
	else
	{
		InsertInTriangle(pMesh, pTargetTri, ver_index);
	}
}

void InsertInTriangle(MESH_PTR pMesh, TRIANGLE_PTR pTargetTri, int ver_index)	//如果插入点在三角边上的插入操作
{
	int index_a, index_b, index_c;
	TRIANGLE_PTR pTri = NULL;
	TRIANGLE_PTR pNewTri = NULL;

	pTri = pTargetTri;	
	if(pTri == NULL)
	{
		return;
	}

	// Inset p into target triangle
	index_a = pTri->i1;
	index_b = pTri->i2;
	index_c = pTri->i3;

	// Insert edge pa, pb, pc
	for(int i=0; i<3; i++)
	{
		// allocate memory
		if(i == 0)
		{
			pNewTri = AddTriangleNode(pMesh, pTri, index_a, index_b, ver_index);
		}
		else if(i == 1)
		{
			pNewTri = AddTriangleNode(pMesh, pTri, index_b, index_c, ver_index);
		}
		else
		{
			pNewTri = AddTriangleNode(pMesh, pTri, index_c, index_a, ver_index);
		}

		// go to next item
		if (pNewTri != NULL)
		{
			pTri = pNewTri;
		}
		else
		{
			pTri = pTri;
		}
	}

	// Get the three sub-triangles
	pTri = pTargetTri;	
	TRIANGLE_PTR pTestTri[3];
	for (int i=0; i< 3; i++)
	{
		pTestTri[i] = pTri->pNext;

		pTri = pTri->pNext;
	}

	// remove the Target Triangle
	RemoveTriangleNode(pMesh, pTargetTri);

	for (int i=0; i< 3; i++)
	{
		// Flip test
		FlipTest(pMesh, pTestTri[i]);
	}
}

void InsertOnEdge(MESH_PTR pMesh, TRIANGLE_PTR pTargetTri, int ver_index)	//如果插入点在三角形内的插入操作
{	
	int index_a, index_b, index_c;
	TRIANGLE_PTR pTri = NULL;
	TRIANGLE_PTR pNewTri = NULL;

	pTri = pTargetTri;	
	if(pTri == NULL)
	{
		return;
	}

	// Inset p into target triangle
	index_a = pTri->i1;
	index_b = pTri->i2;
	index_c = pTri->i3;

	// Insert edge pa, pb, pc
	for(int i=0; i<3; i++)
	{
		// allocate memory
		if(i == 0)
		{
			pNewTri = AddTriangleNode(pMesh, pTri, index_a, index_b, ver_index);
		}
		else if(i == 1)
		{
			pNewTri = AddTriangleNode(pMesh, pTri, index_b, index_c, ver_index);
		}
		else
		{
			pNewTri = AddTriangleNode(pMesh, pTri, index_c, index_a, ver_index);
		}		

		// go to next item
		if (pNewTri != NULL)
		{
			pTri = pNewTri;
		}
		else
		{
			pTri = pTri;
		}
	}

	// Get the two sub-triangles
	pTri = pTargetTri;	
	TRIANGLE_PTR pTestTri[2];
	for (int i=0; i< 2; i++)
	{
		pTestTri[i] = pTri->pNext;
		pTri = pTri->pNext;
	}

	// remove the Target Triangle
	RemoveTriangleNode(pMesh, pTargetTri);

	for (int i=0; i< 2; i++)
	{
		// Flip test
		FlipTest(pMesh, pTestTri[i]);
	}
}

// Precondition: the triangle satisfies CCW order
// Algorithm FlipTest(DT(a,b,c,v1,v2,...,vi), va, vb, vi)
// 1.find the third vertex (vd) of triangle which contains edge vavb // FindThirdVertex()
// 2.if(vi is in circumcircle of abd)  // InCircle()
// 3.    then remove edge vavb, add new edge vivd into DT // UpdateDT()
//		  FlipTest(DT, va, vd, vi)
//		  FlipTest(DT, vd, vb, vi)

bool FlipTest(MESH_PTR pMesh, TRIANGLE_PTR pTestTri)	//插入点后进行的局部调整操作，使新增加的三角形满足Delaunay三角形特性
{
	bool flipped = false;

	int index_a = pTestTri->i1;
	int index_b = pTestTri->i2;
	int index_p = pTestTri->i3;

	int statify[3]={0,0,0};
	int vertex_index;
	int* pi;
	int k = 1;

	// find the triangle which has edge consists of start and end
	TRIANGLE_PTR pTri = pMesh->pTriArr;

	int index_d = -1;
	while (pTri != NULL)
	{
		statify[0] = 0;
		statify[1] = 0;
		statify[2] = 0;

		pi = &(pTri->i1);
		for (int j=0, k = 1; j<3; j++, k*= 2)
		{
			vertex_index = *pi++;
			if(vertex_index == index_a || vertex_index == index_b)
			{
				statify[j] = k;
			}
		}

		switch(statify[0] | statify[1] | statify[2] )
		{
			case 3:
				if(CounterClockWise((VERTEX2D_PTR)(pMesh->pVerArr+index_a), (VERTEX2D_PTR)(pMesh->pVerArr+index_b), (VERTEX2D_PTR)(pMesh->pVerArr+pTri->i3)) < 0)
				{
					index_d = pTri->i3;
				}
				
				break;
			case 5:
				if(CounterClockWise((VERTEX2D_PTR)(pMesh->pVerArr+index_a), (VERTEX2D_PTR)(pMesh->pVerArr+index_b), (VERTEX2D_PTR)(pMesh->pVerArr+pTri->i2)) < 0)
				{
					index_d = pTri->i2;
				}
				
				break;
			case 6: 
				if(CounterClockWise((VERTEX2D_PTR)(pMesh->pVerArr+index_a), (VERTEX2D_PTR)(pMesh->pVerArr+index_b), (VERTEX2D_PTR)(pMesh->pVerArr+pTri->i1)) < 0)
				{
					index_d = pTri->i1;
				}

				break;

			default:
				break;
		}

		if (index_d != -1)
		{
			VERTEX2D_PTR pa = (VERTEX2D_PTR)(pMesh->pVerArr+index_a);
			VERTEX2D_PTR pb = (VERTEX2D_PTR)(pMesh->pVerArr+index_b);
			VERTEX2D_PTR pd = (VERTEX2D_PTR)(pMesh->pVerArr+index_d);
			VERTEX2D_PTR pp = (VERTEX2D_PTR)(pMesh->pVerArr+index_p);
			
			if(InCircle( pa, pb, pp, pd) < 0) // not local Delaunay
			{
				flipped = true;

				// add new triangle adp,  dbp, remove abp, abd.
				// allocate memory for adp
				TRIANGLE_PTR pT1 = AddTriangleNode(pMesh, pTestTri, pTestTri->i1, index_d, pTestTri->i3);				
				// allocate memory for dbp
				TRIANGLE_PTR pT2 = AddTriangleNode(pMesh, pT1, index_d, pTestTri->i2, index_p);				
				// remove abp
				RemoveTriangleNode(pMesh, pTestTri);
				// remove abd
				RemoveTriangleNode(pMesh, pTri);

				FlipTest(pMesh, pT1); // pNewTestTri satisfies CCW order
				FlipTest(pMesh, pT2); // pNewTestTri2  satisfies CCW order

				break;
			}			
		}

		// go to next item	
		pTri = pTri->pNext;
	}

	return flipped;
}

// In circle test, use vector cross product
REAL InCircle(VERTEX2D_PTR pa, VERTEX2D_PTR pb, VERTEX2D_PTR pp, VERTEX2D_PTR  pd)	//判断pp是否在由pa、pb，pc组成的三角形的外接圆上
{
	REAL det;
	REAL alift, blift, plift, bdxpdy, pdxbdy, pdxady, adxpdy, adxbdy, bdxady;

	REAL adx = pa->x - pd->x;
	REAL ady = pa->y - pd->y;

	REAL bdx = pb->x - pd->x;
	REAL bdy = pb->y - pd->y;

	REAL pdx = pp->x - pd->x;
	REAL pdy = pp->y - pd->y;

	bdxpdy = bdx * pdy;
	pdxbdy = pdx * bdy;
	alift = adx * adx + ady * ady;

	pdxady = pdx * ady;
	adxpdy = adx * pdy;
	blift = bdx * bdx + bdy * bdy;

	adxbdy = adx * bdy;
	bdxady = bdx * ady;
	plift = pdx * pdx + pdy * pdy;

	det = alift * (bdxpdy - pdxbdy)
		+ blift * (pdxady - adxpdy)
		+ plift * (adxbdy - bdxady);

	return -det;
}

// Remove a node from the triangle list and deallocate the memory
void RemoveTriangleNode(MESH_PTR pMesh, TRIANGLE_PTR pTri)	//从三角链表中删除三角形
{
	if (pTri == NULL)
	{
		return;
	}

	// remove from the triangle list
	if (pTri->pPrev != NULL)
	{
		pTri->pPrev->pNext = pTri->pNext;
	}
	else // remove the head, need to reset the root node
	{
		pMesh->pTriArr = pTri->pNext;
	}

	if (pTri->pNext != NULL)
	{
		pTri->pNext->pPrev = pTri->pPrev;
	}

	// deallocate memory
	free(pTri);	
}

// Create a new node and add it into triangle list
TRIANGLE_PTR AddTriangleNode(MESH_PTR pMesh, TRIANGLE_PTR pPrevTri, int i1, int i2, int i3)	//从三角链表中插入一个新的三角形
{
	// test if 3 vertices are co-linear
	if(CounterClockWise((VERTEX2D_PTR)(pMesh->pVerArr+i1), (VERTEX2D_PTR)(pMesh->pVerArr+i2), (VERTEX2D_PTR)(pMesh->pVerArr+i3)) == 0)
	{
		return NULL;
	}//共线不进行处理

	// allocate memory
	TRIANGLE_PTR pNewTestTri = (TRIANGLE_PTR)malloc(sizeof(TRIANGLE));//首次为三角链表分配内存

	pNewTestTri->i1 = i1;
	pNewTestTri->i2 = i2;
	pNewTestTri->i3 = i3;

	// insert after prev triangle
	if (pPrevTri == NULL) // add root
	{
		pMesh->pTriArr = pNewTestTri;
		pNewTestTri->pNext = NULL;
		pNewTestTri->pPrev = NULL;
	}
	else
	{
		pNewTestTri->pNext = pPrevTri->pNext;
		pNewTestTri->pPrev = pPrevTri;

		if(pPrevTri->pNext != NULL)	//问题：pPrevTri->next是否一直为NULL
		{
			pPrevTri->pNext->pPrev = pNewTestTri;
		}

		pPrevTri->pNext = pNewTestTri;	//三角形链表超级三角形在链表尾
	}
	
	return pNewTestTri;
}

//求三角网每个三角形的的外心
void CalCenter(MESH_PTR pMesh)
{
    int i1,i2,i3;
    REAL centerx,centery;
    VERTEX2D_PTR p1 = (VERTEX2D_PTR)malloc(sizeof(VERTEX2D));
    VERTEX2D_PTR p2 =(VERTEX2D_PTR)malloc(sizeof(VERTEX2D));
    VERTEX2D_PTR p3 = (VERTEX2D_PTR)malloc(sizeof(VERTEX2D));
    TRIANGLE_PTR pTri = (TRIANGLE_PTR)malloc(sizeof(TRIANGLE));
    pTri =  pMesh->pTriArr;
    while(pTri!=NULL)
    {
        i1=pTri->i1;
        i2=pTri->i2;
        i3=pTri->i3;
        VERTEX2D_PTR pVer1 = (VERTEX2D_PTR)(pMesh->pVerArr+i1);
        VERTEX2D_PTR pVer2 = (VERTEX2D_PTR)(pMesh->pVerArr+i2);
        VERTEX2D_PTR pVer3 = (VERTEX2D_PTR)(pMesh->pVerArr+i3);

        REAL   Xmove=pVer1->x;
        REAL   Ymove=pVer1->y;
        p2->x=pVer2->x-pVer1->x;
        p2->y=pVer2->y-pVer1->y;
        p3->x=pVer3->x-pVer1->x;
        p3->y=pVer3->y-pVer1->y;
        p1->x=0;
        p1->y=0;


        REAL   x1=p2->x,y1=p2->y,x2=p3->x,y2=p3->y;
        REAL   m=2.0*(x1*y2-y1*x2);
        //pTri->center.x=(x1*x1*y2-x2*x2*y1+y1*y2*(y1-y2))/m;
        //pTri->center.y=(x1*x2*(x2-x1)-y1*y1*x2+x1*y2*y2)/m;
        centerx=(x1*x1*y2-x2*x2*y1+y1*y2*(y1-y2))/m;
        centery=(x1*x2*(x2-x1)-y1*y1*x2+x1*y2*y2)/m;
        //radius=distance(center,p[0]);
        centerx+=Xmove;
        centery+=Ymove;
        pTri->center.x=centerx;
        pTri->center.y=centery;

        pTri=pTri->pNext;


//        printf("%lg   %lg",centerx,centery);
    }

}

//寻找每条维诺边，把每条维诺边存入pMesh结构体的pEdgeArr成员变量中
void FindEdge(MESH_PTR pMesh)
{
    TRIANGLE_PTR pTri,pFor;
    VERTEX2D_PTR pVer;
    EDGE_PTR pEdge = pMesh->pEdgeArr;
    EDGE_PTR pNewEdge;
    int Va,Vb,Vp,*p,value =0;
    REAL Xm,Ym,k,k2,X0,Y0,t =0;
    pTri = pMesh->pTriArr;
    //遍历三角链表的每个三角形，分别找出每个三角形的相邻三角形，并把相邻三角形的外心连接形成维诺边
    while(pTri!=NULL)
    {
        p = &(pTri->i1);
        for(int j=0;j<3;j++)
        {
            if(j==0)
            {
                Va = *p++;Vb = *p;Vp = pTri->i3;
            }else if(j==1)
            {
                Va = *p++;Vb = *p;Vp = pTri->i1;

            }else
            {
                Va = *p;Vb = pTri->i1;Vp = pTri->i2;
            }
            pFor=pMesh->pTriArr;
            //在三角链表中寻找与其有共边VaVb的相邻三角形
            while(pFor!=NULL)
            {
                if((pFor->i1 == Va||pFor->i2 == Va||pFor->i3 == Va)&&(pFor->i1 == Vb||pFor->i2== Vb||pFor->i3 == Vb))//找到
                {
                    pNewEdge = (EDGE_PTR)malloc(sizeof(EDGE));
                    pNewEdge->v1.x = pTri->center.x;
                    pNewEdge->v1.y = pTri->center.y;
                    pNewEdge->v2.x = pFor->center.x;
                    pNewEdge->v2.y = pFor->center.y;
                    pEdge->pNext = pNewEdge;
                    pEdge = pNewEdge;
                    pEdge->pNext =NULL;
                    if(pFor!=pTri)
                      value++;

                }

                pFor = pFor->pNext;

            }
            if(value==0)//如果在三角链表中找不到共边VaVb的相邻三角形，则该边是三角网的外边，应向外作中垂线射线
            {
                //Xm和Ym是边VaVb的中点坐标

                Xm = ((pMesh->pVerArr+Va)->x+(pMesh->pVerArr+Vb)->x)/2;
                Ym =((pMesh->pVerArr+Va)->y+(pMesh->pVerArr+Vb)->y)/2;

                k = (pTri->center.y -Ym)/(pTri->center.x -Xm);

                pNewEdge = (EDGE_PTR)malloc(sizeof(EDGE));
                pNewEdge->v1.x = pTri->center.x;
                pNewEdge->v1.y = pTri->center.y;
                REAL yy =(pMesh->pVerArr+Va)->y - (pMesh->pVerArr+Vb)->y;
                REAL xx = (pMesh->pVerArr+Va)->x - (pMesh->pVerArr+Vb)->x;
                //如果边VaVb斜率不为0则k2是它的斜率
                if(yy&&xx)
                {k2 = (yy)/(xx);}
                else
                {k2 = 0;}
                X0 = (pMesh->pVerArr+Vp)->x;
                Y0 = X0*k2-k2*((pMesh->pVerArr+Va)->x)+(pMesh->pVerArr+Va)->y;
                pVer = &pTri->center;
                if(k2!=0)
                {
                    if(k>0) //
                    {
                        if((pMesh->pVerArr+Vp)->y>Y0)
                        t =10;
                        else
                        t=1000;
                    }
                    else
                    {
                        if((pMesh->pVerArr+Vp)->y>Y0)
                        t =1000;
                        else
                        t=10;

                    }
                }
                else
                {
                    if(xx == 0)
                    {
                    if((pMesh->pVerArr+Vp)->x>Xm)
                        t=10;
                    else
                        t=1000;
                    }
                    else
                    {
                        if((pMesh->pVerArr+Vp)->y>Ym)
                            t=10;
                        else
                            t=1000;
                    }

                }
                pNewEdge->v2.x = t;
                pNewEdge->v2.y = t*k-k*Xm+Ym;

                pEdge->pNext = pNewEdge;
                pEdge = pNewEdge;
                pEdge->pNext =NULL;

            }

              value = 0;

        }

        pTri = pTri->pNext;
    }

}