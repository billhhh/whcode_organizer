#include "Tank_Manager.h"
#include <ctime>
#include <windows.h>
using std::vector;

Tank_Manager*  Tank_Manager::instance = NULL;

Tank_Manager::Tank_Manager(){
	init();
}

Tank_Manager::~Tank_Manager(){
	if( instance = NULL){
		delete instance;
		instance = NULL;
	}
}

Tank_Manager* Tank_Manager::getInstance(){
	if( instance == NULL){
		instance = new Tank_Manager();
	}
	return instance;
}

void Tank_Manager::init(){
	tankWorking = 0;
	tankSum = 0;
}

///初始化坦克
void Tank_Manager::init(vector<point3>& vec){
	srand(GetTickCount());
	tankWorking = 0;
	tankSum = vec.size();
	for( size_t i = 0; i < tankSum; ++i){
		point pos;
		pos[0] = vec[i].x; pos[1] = vec[i].y; pos[2] = vec[i].z;
		Tank_Controller* tankCtl = new Tank_Controller(pos);
		Tank_Model* tank;
		int j = rand()%9 / 3;
		switch(j){
		case 0:
			tank = new Tank_Model_TypeA();
			break;
		case 1:
			tank = new Tank_Model_TypeB();
			break;
		case 2:
			tank = new Tank_Model_TypeC();
			break;
		default:
			break;
		}
		tankCtl->initTank(tank);
		tankVec.push_back(tankCtl);
	}
}

std::vector<Tank_Controller*>& Tank_Manager::getTankVec(){
	return tankVec;
}

Tank_Controller* Tank_Manager::getTankWorking(){
	if( !(tankWorking >= 0 && tankWorking < tankSum))
		return NULL;
	return tankVec[tankWorking];
}

int Tank_Manager::getTankWorkingNum() const{
	return tankWorking;
}

int Tank_Manager::getTankSum() const{
	return tankSum;
}

void Tank_Manager::setTankWorking(int i){
	tankWorking = i;
}

///清除所有炮弹
void Tank_Manager::clearShell(){
	for( size_t i = 0; i < tankVec.size(); ++i)
		tankVec[i]->unfire();
}

//重新复活
void Tank_Manager::reStart(){
	int counter = 0;
	for( size_t i = 0; i < tankVec.size();i ++){
		if(!tankVec[i]->getStatus())
			counter ++;
	}
	if (counter >= tankVec.size() - 1){
		for(size_t i = 0; i < tankVec.size();i ++){
			tankVec[i]->setStatus(true);
		}
	}
}

///绘出所有坦克
void Tank_Manager::draw(){
	for(size_t i = 0; i < tankVec.size();i ++){
		if( tankVec[i]->getStatus())
			tankVec[i]->draw();
	}
}