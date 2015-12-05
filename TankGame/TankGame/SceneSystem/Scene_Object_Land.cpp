#include "Scene_Object_Land.h"
#include "../Global.h"

Scene_Object_Land::Scene_Object_Land(){
	radius = 10;
}

Scene_Object_Land::Scene_Object_Land(double x, double y, double z)
:Scene_Object(x, y, z){
	radius = 10;
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

Scene_Object_Land::Scene_Object_Land(point pt)
:Scene_Object(pt){
	radius = 10;
}

Scene_Object_Land::~Scene_Object_Land(){
	gluDeleteQuadric(SP);
}

void Scene_Object_Land::draw(){
	glPushMatrix();
	glTranslatef(pos[0],pos[1],pos[2]);
	glScalef(radius,5,radius);
	SP = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	gluQuadricTexture(SP, GL_TRUE);
	gluSphere(SP,1, 20, 20);
	glPopMatrix();
}