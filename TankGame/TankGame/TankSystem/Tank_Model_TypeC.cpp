#include "Tank_Model_TypeC.h"
#include "../Global.h"

Tank_Model_TypeC::Tank_Model_TypeC(){
	init();
}

Tank_Model_TypeC::~Tank_Model_TypeC(){
	gluDeleteQuadric(pObj1);
	gluDeleteQuadric(pObj2);
}

void Tank_Model_TypeC::init(){
	power = 15;
	width = 6;
	length = 10;
	radius = 10;
	height = 10;
	gHeight = 6.5;
	pObj1=gluNewQuadric();
	pObj2=gluNewQuadric();
}

void Tank_Model_TypeC::draw(){
	glPushMatrix();
	//************************
	glRotatef(angPos,0,1,0);
	glRotatef(angOri,0,1,0);

		glScalef(0.5,0.5,0.5);
		glTranslatef(0,-2,0);
	//***************************
		glPushMatrix();

		//DrawWheels
		glPushMatrix();
		glTranslatef(15.,0.,0.);
		wheel();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-15.,0.,0.);
		wheel();
		glPopMatrix();

		//Draw Body
		glPushMatrix();
		body();
		glPopMatrix();

		//Draw GunTower
		glPushMatrix();
		glTranslatef(0.,10.,-2.);
		guntower();
		glPopMatrix();

		glPopMatrix();
	glPopMatrix();

}

void Tank_Model_TypeC::wheel(){
	point v[12] = {
		{-5.0, 0.0, 10.0}, {-5.0, 5.0, 22.0},
		{-5.0, 10.0, 10.0}, {-5.0, 10.0, -10.0},
		{-5.0, 5.0, -22.0}, {-5.0, 0.0, -10.0},
		{5.0, 0.0, 10.0}, {5.0, 5.0, 22.0},
		{5.0, 10.0, 10.0}, {5.0, 10.0, -10.0},
		{5.0, 5.0, -22.0}, {5.0, 0.0, -10.0}
	};

	glBindTexture( GL_TEXTURE_2D, texture[1] );

	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0.,0.75);glVertex3fv(v[1]);
	glTexCoord2f(0.,0.50);glVertex3fv(v[7]);
	glTexCoord2f(0.26,0.75);glVertex3fv(v[2]);
	glTexCoord2f(0.26,0.50);glVertex3fv(v[8]);
	glTexCoord2f(0.66,0.75);glVertex3fv(v[3]);
	glTexCoord2f(0.66,0.50);glVertex3fv(v[9]);
	glTexCoord2f(0.92,0.75);glVertex3fv(v[4]);
	glTexCoord2f(0.92,0.50);glVertex3fv(v[10]);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0.,1.);glVertex3fv(v[4]);
	glTexCoord2f(0.,0.75);glVertex3fv(v[10]);
	glTexCoord2f(0.26,1.);glVertex3fv(v[5]);
	glTexCoord2f(0.26,0.75);glVertex3fv(v[11]);
	glTexCoord2f(0.66,1.);glVertex3fv(v[0]);
	glTexCoord2f(0.66,0.75);glVertex3fv(v[6]);
	glTexCoord2f(0.92,1.);glVertex3fv(v[1]);
	glTexCoord2f(0.92,0.75);glVertex3fv(v[7]);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.24,0.25);glVertex3fv(v[0]);
	glTexCoord2f(0.,0.375);glVertex3fv(v[1]);
	glTexCoord2f(0.24,0.5);glVertex3fv(v[2]);
	glTexCoord2f(0.64,0.5);glVertex3fv(v[3]);
	glTexCoord2f(0.88,.375);glVertex3fv(v[4]);
	glTexCoord2f(0.64,0.25);glVertex3fv(v[5]);
	glEnd();


	glBegin(GL_POLYGON);
	glTexCoord2f(0.24,0.25);glVertex3fv(v[6]);
	glTexCoord2f(0.,0.375);glVertex3fv(v[7]);
	glTexCoord2f(0.24,0.5);glVertex3fv(v[8]);
	glTexCoord2f(0.64,0.5);glVertex3fv(v[9]);
	glTexCoord2f(0.88,0.375);glVertex3fv(v[10]);
	glTexCoord2f(0.64,0.25);glVertex3fv(v[11]);
	glEnd();
}

void Tank_Model_TypeC::body(){
	point v[8] = {
		{-10.0, 1.0, 20.0}, {-10.0, 11.0, 10.0},
		{-10.0, 11.0, -15.0}, {-10.0, 0.0, -15.0},
		{10.0, 1.0, 20.0}, {10.0, 11.0, 10.0},
		{10.0, 11.0, -15.0}, {10.0, 1.0, -15.0}
	};

	glBindTexture( GL_TEXTURE_2D, texture[2] );

	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0.0,1.0);glVertex3fv(v[0]);
	glTexCoord2f(0.0,0.6);glVertex3fv(v[4]);
	glTexCoord2f(0.15,1.0);glVertex3fv(v[1]);
	glTexCoord2f(0.15,0.6);glVertex3fv(v[5]);
	glTexCoord2f(0.3,1.0);glVertex3fv(v[2]);
	glTexCoord2f(0.3,0.6);glVertex3fv(v[6]);
	glTexCoord2f(0.4,1.0);glVertex3fv(v[3]);
	glTexCoord2f(0.4,0.6);glVertex3fv(v[7]);
	glTexCoord2f(0.6,1.0);glVertex3fv(v[0]);
	glTexCoord2f(0.6,0.6);glVertex3fv(v[4]);
	glEnd();

	//glColor3f(0.031,0.227,0.058);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.1,0.4);glVertex3fv(v[0]);
	glTexCoord2f(0.15,0.6);glVertex3fv(v[1]);
	glTexCoord2f(0.15,0.6);glVertex3fv(v[2]);
	glTexCoord2f(0.15,0.4);glVertex3fv(v[3]);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.1,0.4);glVertex3fv(v[4]);
	glTexCoord2f(0.15,0.6);glVertex3fv(v[5]);
	glTexCoord2f(0.15,0.6);glVertex3fv(v[6]);
	glTexCoord2f(0.15,0.4);glVertex3fv(v[7]);
	glEnd();;
}

void Tank_Model_TypeC::guntower(){
	glPushMatrix();
	glBindTexture( GL_TEXTURE_2D, texture[0] );
	gluQuadricNormals(pObj1,GL_SMOOTH);
	gluQuadricTexture(pObj1, GL_TRUE);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);				// …Ë÷√«ÚŒ∆¿Ì”≥…‰
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	gluSphere(pObj1,10,10,8);
	glPopMatrix();

	glPushMatrix();
	glBindTexture( GL_TEXTURE_2D, texture[0] );
	gluQuadricTexture(pObj2, GL_TRUE);
	gluQuadricNormals(pObj2,GL_SMOOTH);
	glColor3f(0.129, 0.368, 0.129);
	glRotatef(angBtyLR,0,1,0);
	glRotatef(-angBtyUD,1.,0.,0.);
	gluCylinder(pObj2,1.2,1.2,30.,10, 1);
	glPopMatrix();
}
