#include "Shell.h"

Shell::Shell(point& temp){
	for(int i = 0; i < 3 ;i++)
		nextPos[i] = startPos[i] = temp[i];
	rad = 1.0f;
	radiusCollision = 1.0f;
	bStatus = true;
}

Shell::~Shell(){
}

point& Shell::getStartPos(){
	return startPos;
}

point& Shell::getNextPos(){
	return nextPos;
}

void Shell::draw(){
	GLUquadricObj*pObj;
	pObj= gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	  //glTranslatef(nextPos[0]-startPos[0],nextPos[1]-startPos[1],nextPos[2]-startPos[2]);
      glTranslatef(nextPos[0],nextPos[1],nextPos[2]);
	  //glColor3f(0.0f, 0.0f, 0.0f);
	  gluSphere(pObj, rad, 26, 13);
	glPopMatrix();
}

void Shell::setState(double dSpeed,double dYaw, double dPit){
    speed = dSpeed;
	yaw = dYaw;
	pit = dPit;

 	dx = sin(yaw) * cos(pit) * speed;	
	dy = sin(pit) * speed;
	dz = cos(yaw) * cos(pit) * speed;
}

void Shell::move(){
	startPos[0] = nextPos[0];
	nextPos[0] += dx;
	startPos[1] = nextPos[1];
	nextPos[1] += dy;
	startPos[2] = nextPos[2];
	nextPos[2] += dz;

	dy -= 9.8*0.01;
}

void Shell::setRad(double dRad){
	rad = dRad;
}

double Shell::getRad() const{
	return rad;
}

void Shell::unMove(){
	dz =dy =dx = 0;
}

void Shell::setStatus(bool val){
	bStatus = val;
}

bool Shell::getStatus() const{
	return bStatus;
}

void Shell::setRadCollision(double rc){
	radiusCollision = rc;
}

double Shell::getRadCollision() const{
	return radiusCollision;
}