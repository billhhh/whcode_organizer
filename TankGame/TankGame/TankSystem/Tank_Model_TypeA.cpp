#include "Tank_Model_TypeA.h"
#include "../Global.h"

Tank_Model_TypeA::Tank_Model_TypeA(){
	init();
}

Tank_Model_TypeA::~Tank_Model_TypeA(){
	gluDeleteQuadric(pObj1);
	gluDeleteQuadric(pObj2);
	gluDeleteQuadric(pObj3);
	gluDeleteQuadric(pObj4);
}

void Tank_Model_TypeA::init(){
	power = 13;
	width = 6;
	length = 10;
	radius = 10;
	height = 8.5;
	gHeight = 6.0;
	pObj1 = gluNewQuadric();
	pObj2 = gluNewQuadric();
	pObj3 = gluNewQuadric();
	pObj4 = gluNewQuadric();
}

void Tank_Model_TypeA::draw(){
	glPushMatrix();
	//************************
	glRotatef(angPos,0,1,0);
	glRotatef(angOri,0,1,0);
	//***************************
		tank();
	glPopMatrix();
}

void Tank_Model_TypeA::tank(){
	//两个转轴
	glPushMatrix();
	glTranslatef(0.0,0.0,-6.0);
	shaft();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.0,6.0);
	shaft();
	glPopMatrix();

	//履带
	glPushMatrix();
	track();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-11.0,0.0,0.0);
	track();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.0,0.0,0.0);
	track2(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.0,0.0,0.0);
	track2(-1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.0,0.0,0.0);
	track2(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.0,0.0,0.0);
	track2(1);
	glPopMatrix();

	//内部
	glPushMatrix();
	glTranslatef(0.0,0.0,-1.0);
	glRotatef(-90,1.0,0.0,0.0);
	glScalef(4,8,6);
	glutSolidCone(1., 1., 20, 1);
	glPopMatrix();

	//底盘
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	glTranslatef(0.,1.4,0.0);
	glRotatef(-90,1.0,0.0,0.0);
	glScalef(3.9,8,2);
	//		glScalef(7.8,16,4);
	//		glutSolidCube(1.);
	glBegin(GL_QUADS);
	// 前面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); // 纹理和四边形的左上
	// 后面
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
	// 顶面
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); // 纹理和四边形的右上
	// 底面
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); // 纹理和四边形的右下
	// 右面
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); // 纹理和四边形的左上
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); // 纹理和四边形的左下
	// 左面
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); // 纹理和四边形的右下
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); // 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); // 纹理和四边形的左上
	glEnd();

	glPopMatrix();

//	glColor3fv(yellow);
	//**********************************
	glPushMatrix();
	glRotatef(angBtyLR,0,1,0);
	glRotatef(-angBtyUD,1,0,0);
	
	bettery();
	glPopMatrix();
	//************************
}

void Tank_Model_TypeA::track(){
	point track[] = {
		{4., 0, 10.},{7., 0, 10.},{4., -2.8, 7.5},{7., -2.8, 7.5},
		{4., -2.8, -7.5},{7., -2.8, -7.5},{4., 0, -10},{7., 0, -10},
		{4., 2.8, -7.5},{7., 2.8, -7.5},{4., 2.8, 7.5},{7., 2.8, 7.5}
	};
	//glColor3fv(green);

	point vNormal;
	
//	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); 
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);	
	glBegin(GL_QUAD_STRIP);
	getNormal(vNormal,track[0],track[1],track[11]);
	glNormal3fv(vNormal);
	glTexCoord2f(0,1);glVertex3fv(track[0]);
	glTexCoord2f(0,0);glVertex3fv(track[1]);
	glTexCoord2f(0.15,1);glVertex3fv(track[10]);
	glTexCoord2f(0.15,0);glVertex3fv(track[11]);

	getNormal(vNormal,track[11],track[10],track[9]);
	glNormal3fv(vNormal);
	glTexCoord2f(0.85,1);glVertex3fv(track[8]);
	glTexCoord2f(0.85,0);glVertex3fv(track[9]);

	getNormal(vNormal,track[6],track[7],track[9]);
	glNormal3fv(vNormal);
	glTexCoord2f(1,1);glVertex3fv(track[6]);
	glTexCoord2f(1,0);glVertex3fv(track[7]);

	getNormal(vNormal,track[6],track[4],track[5]);
	glNormal3fv(vNormal);
	glTexCoord2f(0.85,1);glVertex3fv(track[4]);
	glTexCoord2f(0.85,0);glVertex3fv(track[5]);

	getNormal(vNormal,track[2],track[3],track[4]);
	glNormal3fv(vNormal);
	glTexCoord2f(0.15,1);glVertex3fv(track[2]);
	glTexCoord2f(0.15,0);glVertex3fv(track[3]);

	getNormal(vNormal,track[0],track[1],track[2]);
	glNormal3fv(vNormal);
	glTexCoord2f(0,1);glVertex3fv(track[0]);
	glTexCoord2f(0,0);glVertex3fv(track[1]);
	glEnd();	
	glPopMatrix();
}

void Tank_Model_TypeA::track2(int f){
	point track2[] = {
		{0, 0.4, 10.},{0, -1.8, 9},{0, -2.8, 7.5},
		{0, -2.8, -7.5},{0, -0.5, -10},{0,2.8,-10},
		{0, 2.8, 9}
	};
	
//	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); 
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);	
	glBegin(GL_POLYGON);
	glNormal3f(-1*f,0,0);
	glTexCoord2f(0.05,0.5);glVertex3fv(track2[0]);
	glTexCoord2f(0.05,0.2);glVertex3fv(track2[1]);
	glTexCoord2f(0.2,0);glVertex3fv(track2[2]);
	glTexCoord2f(0.85,0);glVertex3fv(track2[3]);
	glTexCoord2f(0.95,0.3);glVertex3fv(track2[4]);
	glTexCoord2f(0.95,1);glVertex3fv(track2[5]);
	glTexCoord2f(0.1,1);glVertex3fv(track2[6]);
	//glTexCoord2f(0.1,0.5);glVertex3fv(track2[0]);
	glEnd();
	glPopMatrix();
}

void Tank_Model_TypeA::shaft(){
	glPushMatrix();
	gluQuadricDrawStyle(pObj4, GLU_FILL);
	gluQuadricNormals(pObj4,GLU_SMOOTH);
	glTranslatef(2.0,0.0,0.0);
	glRotatef(-90,0.0,1.0,0.0);
	glTranslatef(0.0,0.0,-5.0);
	glBindTexture(GL_TEXTURE_2D,texture[7]);
	gluQuadricTexture(pObj4,GL_TRUE);
	gluCylinder(pObj4,1.0,1.0,14,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6,0.0,0.0);
	glRotatef(-90,0.0,1.0,0.0);
	glScalef(1,1,1);
	glutSolidTorus(0.8,1.8,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.0,0.0,0.0);
	glRotatef(-90,0.0,1.0,0.0);
	glScalef(1,1,1);
	glutSolidTorus(0.8,1.8,20,20);
	glPopMatrix();
}

void Tank_Model_TypeA::bettery(){
	//炮管
	glPushMatrix();

	gluQuadricDrawStyle(pObj1, GLU_FILL);
	gluQuadricNormals(pObj1,GLU_SMOOTH);
	glTranslatef(0.0,5.5,0.0);
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	gluQuadricTexture(pObj1,GL_TRUE);
	gluCylinder(pObj1,0.8,0.8,16,20,20);
	glPopMatrix();

	glPushMatrix();

	gluQuadricDrawStyle(pObj2, GLU_FILL);
	gluQuadricNormals(pObj2,GLU_SMOOTH);
	glTranslatef(0.0,5.5,0.0);
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	gluQuadricTexture(pObj2,GL_TRUE);
	gluCylinder(pObj2,1.,1.,4,20,20);
	glPopMatrix();

	glPushMatrix();

	gluQuadricDrawStyle(pObj3, GLU_FILL);
	gluQuadricNormals(pObj3,GLU_SMOOTH);
	glTranslatef(0.0,5.5,14.0);
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	gluQuadricTexture(pObj3,GL_TRUE);
	gluCylinder(pObj3,1.,1.,3,20,20);
	glPopMatrix();

	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, green );
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green );

	point triNormal;
	//炮台

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUAD_STRIP);
	getNormal(triNormal,-1.5,7,2,-2.5,4,3,1.5,7,2);
	glNormal3fv(triNormal);
	glTexCoord2f(0.0,1);glVertex3f(-1.5, 7, 2);	
	glTexCoord2f(0.0,0);glVertex3f(-2.5, 4, 3);
	glTexCoord2f(1,1);glVertex3f(1.5, 7, 2);
	glTexCoord2f(1,0);glVertex3f(2.5, 4, 3);


	getNormal(triNormal,2.5, 4, 3,2.6,7,1,3.3,4,1);
	glNormal3fv(triNormal);
	glTexCoord2f(0.0,1);glVertex3f(2.6, 7, 1);
	glTexCoord2f(0.0,0);glVertex3f(3.3, 4, 1);

	getNormal(triNormal,3.3,4,1,2.6,7,-3,3.3,4,-3);		
	glNormal3fv(triNormal);
	glTexCoord2f(1,1);glVertex3f(2.6, 7, -3);
	glTexCoord2f(1,0);glVertex3f(3.3, 4, -3);

	getNormal(triNormal,3.3,4,-3,1.5,7,-4,2.5,4,-5);
	glNormal3fv(triNormal);
	glTexCoord2f(0.0,1);glVertex3f(1.5, 7, -4);
	glTexCoord2f(0.0,0);glVertex3f(2.5, 4, -5);

	getNormal(triNormal,2.5,4,-5,-1.5,7,-4,-2.5,4,-5);
	glNormal3fv(triNormal);
	glTexCoord2f(1,1);glVertex3f(-1.5, 7, -4);
	glTexCoord2f(1,0);glVertex3f(-2.5, 4, -5);

	getNormal(triNormal,-2.5,4,-5,-2.6,7,-3,-3.3,4,-3);
	glNormal3fv(triNormal);
	glTexCoord2f(0.0,1);glVertex3f(-2.6, 7, -3);
	glTexCoord2f(0.0,0);glVertex3f(-3.3, 4, -3);

	getNormal(triNormal,-3.3,4,-3,-2.6,7,1,-3.3,4,1);
	glNormal3fv(triNormal);
	glTexCoord2f(1,1);glVertex3f(-2.6, 7, 1);
	glTexCoord2f(1,0);glVertex3f(-3.3, 4, 1);

	getNormal(triNormal,-3.3,4,1,-1.5,7,2,-2.5,4,3);
	glNormal3fv(triNormal);
	glTexCoord2f(0.0,1);glVertex3f(-1.5, 7, 2);	
	glTexCoord2f(0.0,0);glVertex3f(-2.5, 4, 3);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);	
	glNormal3f(0,0,1);
	glTexCoord2f(0.0,0.7);glVertex3f(-1.5, 7, 2);
	glTexCoord2f(0.0,0.3);glVertex3f(1.5, 7, 2);
	glTexCoord2f(0.3,0);glVertex3f(2.6, 7, 1);
	glTexCoord2f(0.7,0);glVertex3f(2.6, 7, -3);
	glTexCoord2f(1.0,0.3);glVertex3f(1.5, 7, -4);
	glTexCoord2f(1.0,0.7);glVertex3f(-1.5, 7, -4);
	glTexCoord2f(0.7,1.0);glVertex3f(-2.6, 7, -3);
	glTexCoord2f(0.3,1.0);glVertex3f(-2.6, 7, 1);
	//glTexCoord2f(1.0,1);glVertex3f(-1.5, 7, 2);
	glEnd();
	glPopMatrix();
}

