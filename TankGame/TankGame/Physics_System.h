#ifndef _H_PHYSICS_SYSTEM_H
#define _H_PHYSICS_SYSTEM_H

#include "TankSystem/Tank_Manager.h"
#include "SceneSystem/Scene_Manager.h"

class PhysicsSystem{
private:
	PhysicsSystem();
	static PhysicsSystem* instance;

	Tank_Manager* tank_manager;
	Scene_Manager* scene_manager;
public:
	static PhysicsSystem* getInstance();
	~PhysicsSystem();

	void init();

	bool checkIsOut(Tank_Controller*);
	bool checkCollision(Tank_Controller*,int);
	bool checkCollisionShell(int i,int j);
	bool checkCollisionOther(int i);
	void collisionProcess(int i);
	void shellProcess();
public:
}; 

#endif