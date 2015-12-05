#include "Scene_Manager.h"
#include "windows.h"
#include "../Global.h"
using std::vector;

Scene_Manager* Scene_Manager::instance = NULL;

Scene_Manager::Scene_Manager(){
	init();
}

Scene_Manager::~Scene_Manager(){
	destroyAllObject();

	if( instance = NULL){
		delete instance;
		instance = NULL;
	}
}

//返回实例
Scene_Manager* Scene_Manager::getInstance(){
	if( instance == NULL){
		instance = new Scene_Manager();
	}
	return instance;
}

//初始化场景
void Scene_Manager::init(){
	srand(GetTickCount());
	ObjectSum = 6;
	for( size_t i = 0; i < ObjectSum; ++i){
		Scene_Object* pSO = new Scene_Object_Land(rand()%(2*SCENE_WIDTH)-(SCENE_WIDTH), 0, rand()%(2*SCENE_HEIGHT)-(SCENE_HEIGHT));
		if( pSO->getPos()[0] < 0)
			pSO->getPos()[0] = max(pSO->getPos()[0], SCENE_WIDTH + pSO->getRadius());
		else
			pSO->getPos()[0] = min(pSO->getPos()[0], SCENE_WIDTH - pSO->getRadius());
		if( pSO->getPos()[2] < 0)
			pSO->getPos()[2] = max(pSO->getPos()[2], SCENE_HEIGHT + pSO->getRadius());
		else
			pSO->getPos()[2] = min(pSO->getPos()[2], SCENE_HEIGHT - pSO->getRadius());

		addObject(pSO);
	}
}

bool Scene_Manager::addObject(Scene_Object* obj){
	objectVec.push_back(obj);
	return true;
}

//销毁所有对象
bool Scene_Manager::destroyAllObject(){
	vector<Scene_Object*>::iterator iter = objectVec.begin();
	for(; iter!= objectVec.end(); ++iter){
		delete *iter;
	}
	objectVec.clear();
	return true;
}

//获取场景对象列表
std::vector<Scene_Object*>& Scene_Manager::getObjectVec(){
	return objectVec;
}

//获取场景对象总数
int Scene_Manager::getObjectSum() const{
	return ObjectSum;
}

//绘出所有场景对象
void Scene_Manager::drawObject(){
	vector<Scene_Object*>::iterator iter = objectVec.begin();
	for(; iter!= objectVec.end(); ++iter){
		(*iter)->draw();
	}
}

//绘出场景
void Scene_Manager::draw(){
	drawObject();

	glPushMatrix();
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D,texture[4]);
	glTranslatef(0.,-1.4,0.0);
	glScalef(SCENE_WIDTH,0.5,SCENE_HEIGHT);
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

	glBindTexture(GL_TEXTURE_2D,texture[7]);
	glPushMatrix();
	glRotatef(90,1,0,0);
	GLUquadric* skyObj = gluNewQuadric();
	gluQuadricTexture(skyObj,GL_TRUE);
	gluSphere(skyObj,300,100,100);
	glPopMatrix();
}

const int Scene_Manager::getSceneWidth(){
	return SCENE_WIDTH;
}

const int Scene_Manager::getSceneHeight(){
	return SCENE_HEIGHT;
}