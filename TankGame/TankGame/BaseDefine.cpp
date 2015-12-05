#include "BaseDefine.h"

void myNormal(point &N,const point &A,const point &B,const point &C){
	point AB,AC;
	for(int i = 0; i < 3 ; i++){
		AB[i] = B[i] - A[i];
		AC[i] = C[i] - A[i];
	}

	N[0] = AB[1]*AC[2]-AC[1]*AB[2];
	N[1] = AB[2]*AC[0]-AC[2]*AB[0];
	N[2] = AB[0]*AC[1]-AC[0]*AB[1];
}

void getNormal(point triNormal, point v1, point v2, point v3){
	point vec1, vec2;//, triNormal;
	vec1[0] = v2[0] - v1[0];
	vec1[1] = v2[1] - v1[1];
	vec1[2] = v2[2] - v1[2];
	vec2[0] = v3[0] - v2[0];
	vec2[1] = v3[1] - v2[1];
	vec2[2] = v3[2] - v2[2];
	triNormal[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	triNormal[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	triNormal[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	//return &triNormal;
	//glNormal3fv(triNormal); 
}

void getNormal(point triNormal, float v1_x, float v1_y, float v1_z, float v2_x, float v2_y, float v2_z, float v3_x, float v3_y, float v3_z){
	point vec1, vec2;//, triNormal;
	vec1[0] = v2_x - v1_x;
	vec1[1] = v2_y - v1_y;
	vec1[2] = v2_z - v1_z;
	vec2[0] = v3_x - v2_x;
	vec2[1] = v3_y - v2_y;
	vec2[2] = v3_z - v2_z;
	triNormal[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	triNormal[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	triNormal[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	//return &triNormal;
	//glNormal3fv(triNormal); 
}

double getDistance(point pt1, point pt2){
	double dist = (pt1[0]-pt2[0])*(pt1[0]-pt2[0])+
		(pt1[1]-pt2[1])*(pt1[1]-pt2[1])+(pt1[2]-pt2[2])*(pt1[2]-pt2[2]);
	return sqrt(dist);
}