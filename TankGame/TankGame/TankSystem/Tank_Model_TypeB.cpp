#include "Tank_Model_TypeB.h"
#include "../Global.h"

Tank_Model_TypeB::Tank_Model_TypeB(){
	init();
}

Tank_Model_TypeB::~Tank_Model_TypeB(){
	gluDeleteQuadric(LG);
	gluDeleteQuadric(LG2);
	gluDeleteQuadric(RG);
	gluDeleteQuadric(RG2);
	gluDeleteQuadric(SP);
}

void Tank_Model_TypeB::init(){
	power = 13;
	width = 6;
	length = 10;
	radius = 8;
	height = 6;
	gHeight = 4.5;
	SP = gluNewQuadric();
	LG = gluNewQuadric();
	LG2 = gluNewQuadric();
	RG = gluNewQuadric();
	RG2 = gluNewQuadric();
}

void Tank_Model_TypeB::draw(){
	glPushMatrix();
	//************************
	glRotatef(angPos,0,1,0);
	glRotatef(180,0,1,0);
		glScalef(2,2,2);
		//***************************
			glPushMatrix();
				glTranslatef(0,-1.0,0);
				glRotatef(-90,1,0,0);
				glTranslatef(0,-5,0);
					glPushMatrix();
						glPushMatrix();
							//****************
							glTranslatef(0.,4.5,2.6);
							glRotatef(angBtyLR,0,0,1);
							glRotatef(angBtyUD,1,0,0);
							glTranslatef(0.,-4.5,-2.6);
							//**************
							bettery();
						glPopMatrix();
					body();
					track_L();
					track_R();
					glPopMatrix();
			glPopMatrix();
	glPopMatrix();
}

void Tank_Model_TypeB::track_L(void){
	glPushMatrix();
	glTranslatef(-6 ,0.0 ,0.0);
	track_R();
	glPopMatrix();
}

void Tank_Model_TypeB::track_R(){
	point track[12] = {
		{2,0,1},{2,1,2},{2,9,2},
		{2,10,1},{2,9,0},{2,1,0},
		{4,0,1},{4,1,2},{4,9,2},
		{4,10,1},{4,9,0},{4,1,0}
	};
	//»æÖÆÂÄ´ø
	//	glColor3f(0.42,0.7,0.14);
	point myN;
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUAD_STRIP);
	myNormal(myN,track[0],track[7],track[1]);
	glNormal3fv(myN);
	glTexCoord2f(0,1);glVertex3fv(track[0]);
	glTexCoord2f(0,0);glVertex3fv(track[6]);
	glTexCoord2f(0.15,1);glVertex3fv(track[1]);
	glTexCoord2f(0.15,0);glVertex3fv(track[7]);

	myNormal(myN,track[1],track[8],track[2]);
	glNormal3fv(myN);
	glTexCoord2f(0.85,1);glVertex3fv(track[2]);
	glTexCoord2f(0.85,0);glVertex3fv(track[8]);

	myNormal(myN,track[2],track[9],track[3]);
	glNormal3fv(myN);
	glTexCoord2f(1,1);glVertex3fv(track[3]);
	glTexCoord2f(1,0);glVertex3fv(track[9]);

	myNormal(myN,track[3],track[10],track[4]);
	glNormal3fv(myN);
	glTexCoord2f(0.85,1);glVertex3fv(track[4]);
	glTexCoord2f(0.85,0);glVertex3fv(track[10]);

	myNormal(myN,track[4],track[11],track[5]);
	glNormal3fv(myN);
	glTexCoord2f(0.15,1);glVertex3fv(track[5]);
	glTexCoord2f(0.15,0);glVertex3fv(track[11]);

	myNormal(myN,track[5],track[0],track[6]);
	glNormal3fv(myN);
	glTexCoord2f(0,1);glVertex3fv(track[0]);
	glTexCoord2f(0,0);glVertex3fv(track[6]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,texture[2]);
	glBegin(GL_POLYGON);
	glNormal3f(-1.0,0.0,0.0);
	glTexCoord2f(0,0.5);glVertex3fv(track[0]);
	glTexCoord2f(0.1,1.0);glVertex3fv(track[1]);
	glTexCoord2f(0.9,1);glVertex3fv(track[2]);
	glTexCoord2f(1,0.5);glVertex3fv(track[3]);
	glTexCoord2f(0.9,0);glVertex3fv(track[4]);
	glTexCoord2f(0.1,0);glVertex3fv(track[5]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,texture[2]);
	glBegin(GL_POLYGON);
	glNormal3f(1.0,0.0,0.0);
	glTexCoord2f(0,0.5);glVertex3fv(track[6]);
	glTexCoord2f(0.1,1.0);glVertex3fv(track[7]);
	glTexCoord2f(0.9,1);glVertex3fv(track[8]);
	glTexCoord2f(1,0.5);glVertex3fv(track[9]);
	glTexCoord2f(0.9,0);glVertex3fv(track[10]);
	glTexCoord2f(0.1,0);glVertex3fv(track[11]);
	glEnd();
}

void Tank_Model_TypeB::body(void){
	point body_v[12] ={
		{2.5,2,2.5},{-2.5,2,2.5},{-2.5,8,2.5},{2.5,8,2.5},
		{3.5,1.5,1.5},{-3.5,1.5,1.5},{-3.5,8.5,1.5},{3.5,8.5,1.5},
		{2.5,2,0.5},{-2.5,2,0.5},{-2.5,8,0.5},{2.5,8,0.5}
	};

	point myN;
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUAD_STRIP);
	myNormal(myN,body_v[0],body_v[1],body_v[5]);
	glNormal3fv(myN);
	glTexCoord2f(0,0.14);glVertex3fv(body_v[0]);
	glTexCoord2f(0,0);glVertex3fv(body_v[4]);
	glTexCoord2f(0.6,0.14);glVertex3fv(body_v[1]);
	glTexCoord2f(0.7,0);glVertex3fv(body_v[5]);

	myNormal(myN,body_v[1],body_v[2],body_v[6]);
	glNormal3fv(myN);
	glTexCoord2f(0,0.14);glVertex3fv(body_v[2]);
	glTexCoord2f(0,0);glVertex3fv(body_v[6]);

	myNormal(myN,body_v[2],body_v[3],body_v[7]);
	glNormal3fv(myN);
	glTexCoord2f(0.6,0.14);glVertex3fv(body_v[3]);
	glTexCoord2f(0.7,0);glVertex3fv(body_v[7]);

	myNormal(myN,body_v[3],body_v[0],body_v[4]);
	glNormal3fv(myN);
	glTexCoord2f(0,0.14);glVertex3fv(body_v[0]);
	glTexCoord2f(0,0);glVertex3fv(body_v[4]);	
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUAD_STRIP);
	myNormal(myN,body_v[4],body_v[9],body_v[5]);
	glNormal3fv(myN);
	glTexCoord2f(0,0.14);glVertex3fv(body_v[8]);
	glTexCoord2f(0,0);glVertex3fv(body_v[4]);
	glTexCoord2f(0.6,0.14);glVertex3fv(body_v[9]);
	glTexCoord2f(0.7,0);glVertex3fv(body_v[5]);

	myNormal(myN,body_v[9],body_v[10],body_v[6]);
	glNormal3fv(myN);
	glTexCoord2f(0,0.14);glVertex3fv(body_v[10]);
	glTexCoord2f(0,0);glVertex3fv(body_v[6]);

	myNormal(myN,body_v[10],body_v[11],body_v[7]);
	glNormal3fv(myN);
	glTexCoord2f(0.6,0.14);glVertex3fv(body_v[11]);
	glTexCoord2f(0.7,0);glVertex3fv(body_v[7]);

	myNormal(myN,body_v[11],body_v[8],body_v[4]);
	glNormal3fv(myN);
	glTexCoord2f(0,0.14);glVertex3fv(body_v[8]);
	glTexCoord2f(0,0);glVertex3fv(body_v[4]);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_POLYGON);
	glNormal3f(0.0,0.0,-1.0);
	glTexCoord2f(0,0);glVertex3fv(body_v[8]);
	glTexCoord2f(0.5,0);glVertex3fv(body_v[9]);
	glTexCoord2f(0,0.6);glVertex3fv(body_v[10]);
	glTexCoord2f(0.5,0.6);glVertex3fv(body_v[11]);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_POLYGON);          
	glNormal3f(0.0,0.0,1.0);
	glTexCoord2f(0.0,0.0); glVertex3fv(body_v[0]);
	glTexCoord2f(0.5,0); glVertex3fv(body_v[1]);
	glTexCoord2f(0, 0.6); glVertex3fv(body_v[2]);
	glTexCoord2f(0.5, 0.6); glVertex3fv(body_v[3]);
	glEnd();
}

void Tank_Model_TypeB::bettery(void){
	ball();
	gun();
}

void Tank_Model_TypeB::ball(void){
	glColor3f(0.42,0.56,0.14);
	glPushMatrix();
	glTranslatef(0.,4.5,2.6);
	glScalef(2.,2.,1.2);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	gluQuadricTexture(SP, GL_TRUE);
	gluSphere(SP,.8, 20, 20);
	glPopMatrix();
}

void Tank_Model_TypeB::gun(void){
	//	glColor3f(0.42,0.56,0.14);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glPushMatrix();	
	glRotatef(2., 0., 0., 1.);
	glTranslatef( -0.5, 5., 2.7);
	glRotatef(270., 1., 0., 0.);
	
	gluQuadricTexture(LG, GL_TRUE);
	gluCylinder(LG, 0.15, 0.15, 4., 10, 1);
	glPopMatrix();


	glPushMatrix();
	glRotatef(2., 0., 0., 1.);
	glTranslatef( -0.5, 9., 2.7);
	glRotatef(270., 1., 0., 0.);
	
	gluQuadricTexture(LG2, GL_TRUE);
	gluCylinder(LG2, 0.2, 0.2, 0.5, 10, 1);
	glPopMatrix();


	glPushMatrix();	
	glRotatef(358., 0., 0., 1.);
	glTranslatef( 0.5, 5., 2.7);
	glRotatef(270., 1., 0., 0.);
	
	gluQuadricTexture(RG, GL_TRUE);
	gluCylinder(RG, 0.15, 0.15, 4., 10, 1);	
	glPopMatrix();

	glPushMatrix();
	glRotatef(358., 0., 0., 1.);
	glTranslatef( 0.5, 9., 2.7);
	glRotatef(270., 1., 0., 0.);
	
	gluQuadricTexture(RG2, GL_TRUE);
	gluCylinder(RG2, 0.2, 0.2, 0.5, 10, 1);

	glPopMatrix();
}