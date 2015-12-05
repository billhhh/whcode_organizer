#include "Physics_System.h"
using namespace std;
PhysicsSystem* PhysicsSystem::instance = NULL;

PhysicsSystem::PhysicsSystem(){
	init();
}

PhysicsSystem::~PhysicsSystem(){
	if( instance = NULL){
		delete instance;
		instance = NULL;
	}
}

//返回实例
PhysicsSystem* PhysicsSystem::getInstance(){
	if( instance == NULL){
		instance = new PhysicsSystem();
	}
	return instance;
}

//初始化场景
void PhysicsSystem::init(){

}

//检测是否出边界
bool PhysicsSystem::checkIsOut(Tank_Controller* tank){
	if(tank->getNowPos()[0] > -Scene_Manager::getSceneWidth() &&
		tank->getNowPos()[0] < Scene_Manager::getSceneWidth() &&
		tank->getNowPos()[2] > -Scene_Manager::getSceneHeight() &&
		tank->getNowPos()[2] < Scene_Manager::getSceneHeight()){
		return false;
	}else
		return true;
}

///检测是否发生碰撞
bool PhysicsSystem::checkCollision(Tank_Controller* tank, int tankOnWork){
	vector<Scene_Object*> objectVec = scene_manager->getInstance()->getObjectVec();
	vector<Scene_Object*>::iterator iter = objectVec.begin();
	for(; iter != objectVec.end(); ++iter){
		if( getDistance(tank->getNowPos(), (*iter)->getPos()) < tank->getCollisionRad()+(*iter)->getRadius())
			return true;
	}

	vector<Tank_Controller*> tankVec = tank_manager->getInstance()->getTankVec();
	for( size_t i = 0; i < tankVec.size(); ++i){
		if( i == tankOnWork)
			continue;
		if(!tankVec[i]->getStatus())
			continue;
		if( getDistance(tankVec[i]->getNowPos(), tankVec[tankOnWork]->getNowPos())< 
			tankVec[i]->getCollisionRad()+ tankVec[tankOnWork]->getCollisionRad())
			return true;
	}
	return false;
}

///检测炮弹和其他坦克的碰撞
bool PhysicsSystem::checkCollisionShell(int i, int j){
	vector<Tank_Controller*> tankVec = tank_manager->getInstance()->getTankVec();
	double dist = getDistance(tankVec[i]->getShellPos(), tankVec[j]->getNowPos());
	double rad = tankVec[i]->getShellRad()+tankVec[j]->getCollisionRad();
	if( dist< rad)
		return true;
	else
		return false;
}

///检测炮弹和场景的碰撞
bool PhysicsSystem::checkCollisionOther(int num){
	vector<Tank_Controller*> tankVec = tank_manager->getInstance()->getTankVec();
	vector<Scene_Object*> objectVec = scene_manager->getInstance()->getObjectVec();
	vector<Scene_Object*>::iterator iter = objectVec.begin();
	for(; iter != objectVec.end(); ++iter){
		double dist = getDistance(tankVec[num]->getShellPos(),(*iter)->getPos());
		double rad = tankVec[num]->getShellRad()+(*iter)->getRadius();
		if( dist < rad)
			return true;
	}
	return false;
}

///坦克冲突处理
void PhysicsSystem::collisionProcess(int i){
	Tank_Controller* tank = tank_manager->getInstance()->getTankVec()[i];
	if(checkIsOut(tank) || checkCollision( tank, i)){
		tank->unMove();
		char temp = 's';
		int counter = 0;
		while(checkCollision( tank, i)){
			tank->move(temp);
			if (checkIsOut( tank)){
				if(temp == 's') temp = 's';
				if(temp == 'w') temp = 'w';
			}
			if(counter > 1000){
				point pointTmp = {0,0.5,0};
				tank->setNowPos(pointTmp);
			}
			//counter++;
		}
	}
}

//炮弹处理
void PhysicsSystem::shellProcess(){
	vector<Tank_Controller*> tankVec = tank_manager->getInstance()->getTankVec();
	for( size_t i = 0; i < tankVec.size(); ++i){
		if( tankVec[i]->isShellExist()){
			tankVec[i]->moveShell();
			for(size_t j = 0; j < tankVec.size(); ++j){
				if( j == i) continue;
				if ( tankVec[j]->getStatus()){
					if( checkCollisionShell(i, j)){
						tankVec[i]->explosionShell();
						tankVec[j]->setStatus(false);
						break;
					}
				}
			}
			if( checkCollisionOther(i))
				tankVec[i]->explosionShell();
		}
	}
}
