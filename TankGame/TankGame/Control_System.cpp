#include "Control_System.h"
#include "windows.h";
using namespace std;

Control_System* Control_System::instance = NULL;

Control_System::Control_System(){
	init();
}

Control_System::~Control_System(){
	if( scene_manager != NULL){
		delete scene_manager;
		scene_manager = NULL;
	}
	if( tank_manager != NULL){
		delete tank_manager;
		tank_manager = NULL;
	}

	if( instance = NULL){
		delete instance;
		instance = NULL;
	}
}

//返回实例
Control_System* Control_System::getInstance(){
	if( instance == NULL){
		instance = new Control_System();
	}
	return instance;
}

//初始化场景
void Control_System::init(){
	NOBODY = true;
	LOCK_VIEW_ANGLE = true;

	bW = bS = bA = bD = false;
	bUp = bDown = bLeft = bRight = false;
	bBlank = false;

	initTank();
	srand(GetTickCount());
}

void Control_System::initTank(){
	int tankSum = 9;
	vector<point3> tankPosVec;
	point3 tankPos;
	for (size_t i = 0; i < tankSum; ++i){
		tankPos.x = rand()%(2*(Scene_Manager::getSceneWidth()-30))-(Scene_Manager::getSceneWidth()-30);
		tankPos.y = 0.5;
		tankPos.z = rand()%(2*(Scene_Manager::getSceneHeight()-30))-(Scene_Manager::getSceneHeight()-30);
		tankPosVec.push_back(tankPos);
	}
	tank_manager->getInstance()->init(tankPosVec);
}

void Control_System::cameraMove(GLfloat& camYaw,GLfloat & camPitch,GLfloat& camRadius,
								GLfloat& camPosX,GLfloat& camPosY,GLfloat& camPosZ){
	if(LOCK_VIEW_ANGLE){
		Tank_Controller* tank = tank_manager->getInstance()->getTankWorking();
		if( tank != NULL)
			cameraMoveSub(tank,camYaw,camPitch,camRadius,camPosX,camPosY,camPosZ);
	}
}

void Control_System::cameraMoveSub(Tank_Controller* tank,GLfloat& camYaw,GLfloat& camPitch,
								   GLfloat& camRadius,GLfloat& camPosX,GLfloat& camPosY,GLfloat& camPosZ){
	camYaw = tank->getAngleOrigin();
	camPosX = tank->getNowPos()[0];
	camPosY = tank->getNowPos()[1];	
	camPosZ = tank->getNowPos()[2];
}

void Control_System::keyboardFunc(unsigned int key, int x, int y){
	if( key == 32)
		tank_manager->getInstance()->getTankWorking()->fire();
	switch(key){
	case 'w':	bW = true;break;
	case 's':	bS = true;break;
	case 'a':	bA = true;break;
	case 'd':	bD = true;break;
	case 'R':   
		reStart();
	default:
		break;
	}
}

void Control_System::keyboardUpFunc(unsigned int key, int x, int y){
	switch(key){
	case 'w':	bW = false;break;
	case 's':	bS = false;break;
	case 'a':	bA = false;break;
	case 'd':	bD = false;break;
	default:
		break;
	}
}

void Control_System::specialFunc(unsigned int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP:	bUp = true;break;
	case GLUT_KEY_DOWN:	bDown = true;break;
	case GLUT_KEY_LEFT:	bLeft = true;break;
	case GLUT_KEY_RIGHT:bRight = true;break;
	default:
		break;
	}
}

void Control_System::specialUpFunc(unsigned int key, int x, int y){
	switch(key){
	case GLUT_KEY_UP:	bUp = false;break;
	case GLUT_KEY_DOWN:	bDown = false;break;
	case GLUT_KEY_LEFT:	bLeft = false;break;
	case GLUT_KEY_RIGHT:bRight = false;break;
	default:
		break;
	}
}

void Control_System::idleKeyFunc(){
	Tank_Controller* tank = tank_manager->getInstance()->getTankWorking();
	if(bUp) tank->turnUpBettery();
	if(bDown) tank->turnDownBettery();
	if(bLeft) tank->turnLeftBettery();
	if(bRight) tank->turnRightBettery();
	if(bW) tank->moveUp();
	if(bS) tank->moveDown();
	if(bA) tank->turnLeft();
	if(bD) tank->turnRight();

	physicsSystem->getInstance()->collisionProcess(tank_manager->getInstance()->getTankWorkingNum());
}

void Control_System::idleFunc(){
	///当前使用该策略
	computerAI();
}

////计算机坦克智能，可替换
void Control_System::computerAI(){
	srand(GetTickCount());
	vector<Tank_Controller*> tankVec = tank_manager->getInstance()->getTankVec();
	int tankOnWork = tank_manager->getInstance()->getTankWorkingNum();
	for(size_t j = 0;j < tankVec.size(); ++j){
		if(j == tankOnWork && !NOBODY)
			continue;
		tankVec[j]->move(tankVec[j]->getDirTank());
		tankVec[j]->turnBettery(tankVec[j]->getDirBty());
		physicsSystem->getInstance()->collisionProcess(j);

		if( rand()% 100 < 1)
			tankVec[j]->fire();
	}
}

void Control_System::computerCmd(){
	srand(GetTickCount());
	char key;
	int temp;
	vector<Tank_Controller*> tankVec = tank_manager->getInstance()->getTankVec();
	int tankOnWork = tank_manager->getInstance()->getTankWorkingNum();
	for(size_t j = 0;j < tankVec.size(); ++j){
		if(j == tankOnWork && !NOBODY)
			continue;
		temp = rand()%100;
		if(temp < 25)
			key = 'a';
		else if(temp >= 25 && temp < 50)
			key = 'd';
		else if(temp >= 50 && temp < 75)
			key = 'w';
		else if(temp >= 75 && temp < 90)
			key = 's';
		else
			key = 0;
		tankVec[j]->setDirTank(key);

		temp = rand()%100;
		if(temp < 25)
			key = GLUT_KEY_LEFT;
		else if(temp >= 25 && temp < 50)
			key = GLUT_KEY_RIGHT;
		else if(temp >= 50 && temp < 80)
			key = GLUT_KEY_UP;
		else if(temp >= 80 && temp < 95)
			key = GLUT_KEY_DOWN;
		else if(temp >= 95 && temp < 100)
			key = 0;
		tankVec[j]->setDirBty(key);
	}
}

///选中坦克
void Control_System::selectTank(int number){
	NOBODY = false;
	tank_manager->getInstance()->setTankWorking(number -1);
}

int Control_System::getSelectedTank() const{
	return tank_manager->getInstance()->getTankWorkingNum();
}

void Control_System::mainMenu(int number){
	if(number == 1)
		LOCK_VIEW_ANGLE = !LOCK_VIEW_ANGLE;

	if(number == 2)
		NOBODY = true;
	else
		NOBODY = false;
}

int Control_System::getTankSum() const{
	return tank_manager->getInstance()->getTankSum();
}

void Control_System::getFirstView(GLfloat& camX, GLfloat& camY, GLfloat& camZ,
								  GLfloat& camPosX, GLfloat& camPosY, GLfloat& camPosZ, 
								  GLfloat& camUpX, GLfloat& camUpY, GLfloat& camUpZ){
	Tank_Controller* tank = tank_manager->getInstance()->getTankWorking();
	double tempX = tank->getNowPos()[0];
	double tempY = tank->getNowPos()[1];
	double tempZ = tank->getNowPos()[2];

	camX = tempX;
	camY = tempY + tank->getHeight();
	camZ = tempZ;

	tempX = (tank->getAngleOrigin()+tank->getAnglePos()+tank->getAngleBetteryLR())*2*PI/360;
	tempY = tank->getAngleBetteryUD()*2*PI/360;
	tempZ = 10;

	camPosX = camX +sin(tempX) * cos(tempY) * tempZ;	
	camPosY = camY +sin(tempY) * tempZ;
	camPosZ = camZ +cos(tempX) * cos(tempY) * tempZ;

	tempY = tempY + 90*2*PI/360;

	camUpX = sin(tempX) * cos(tempY) * tempZ;	
	camUpY = sin(tempY) * tempZ;
	camUpZ = cos(tempX) * cos(tempY) * tempZ;
}

void Control_System::unFireTank(){
	physicsSystem->getInstance()->shellProcess();
}

void Control_System::reStart(){
	tank_manager->getInstance()->clearShell();
	tank_manager->getInstance()->reStart();
}

void Control_System::drawAll(GLenum mode){
	if( mode == GL_RENDER){
		scene_manager->getInstance()->draw();
	}
	int tankNum = getTankSum();

	vector<Tank_Controller*> tankVec = tank_manager->getInstance()->getTankVec();
	for (size_t i = 0; i < tankNum; ++i){
		if( mode == GL_SELECT) 
			glPushName(i);
		if( tankVec[i]->getStatus())
			tankVec[i]->draw();
	}
}
