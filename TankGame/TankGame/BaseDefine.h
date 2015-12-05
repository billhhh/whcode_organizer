#ifndef _H_BASEDEFINE_H
#define _H_BASEDEFINE_H

#include <stdlib.h>
#include <glut.h>
#include <math.h>
#define PI 3.1415926535898
typedef GLfloat point [3];
struct point3{
	int x;
	int y;
	int z;
};

//求取法向量
void myNormal(point &N,const point &A,const point &B,const point &C);
//计算法向量
void getNormal(point triNormal, float v1_x, float v1_y, float v1_z, float v2_x, float v2_y, float v2_z, float v3_x, float v3_y, float v3_z);

void getNormal(point triNormal, point v1, point v2, point v3);

double getDistance(point pt1, point pt2);

#endif