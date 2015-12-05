#ifndef _H_CONTROLSYSTEM_H
#define _H_CONTROLSYSTEM_H

#include "TankSystem/Tank_Manager.h"
#include "SceneSystem/Scene_Manager.h"
#include "Physics_System.h"

class Control_System{
private:
	Control_System();

public:
	static Control_System* getInstance();
	~Control_System();

	void init();
	void initTank();

	void drawAll(GLenum mode);
	void cameraMove(GLfloat &camYaw,GLfloat& camPitch,GLfloat& camRadius,
		GLfloat& camPosX,GLfloat& camPosY,GLfloat& camPosZ);
	void cameraMoveSub(Tank_Controller* tank,GLfloat& camYaw,GLfloat& camPitch,GLfloat& camRadius,
		GLfloat& camPosX,GLfloat& camPosY,GLfloat& camPosZ);
	void keyboardFunc(unsigned int key, int x, int y);
	void keyboardUpFunc(unsigned int key, int x, int y);
	void specialFunc(unsigned int key, int x, int y);
	void specialUpFunc(unsigned int key, int x, int y);
	void idleFunc();
	void idleKeyFunc();
	void computerAI();
	void computerCmd();
	void selectTank(int number);
	void mainMenu(int number);
	int getSelectedTank() const;
	void getFirstView(GLfloat &camYaw,GLfloat & camPitch,GLfloat& camRadius,
		GLfloat& camPosX,GLfloat& camPosY,GLfloat& camPosZ, 
		GLfloat&camUpX, GLfloat& camUpY,GLfloat& camUpZ);

	void unFireTank();
	void reStart();
	int getTankSum() const;

private:
	static Control_System* instance;

	Tank_Manager* tank_manager;
	Scene_Manager* scene_manager;
	PhysicsSystem* physicsSystem;

	bool NOBODY;				//是否全自动
	bool LOCK_VIEW_ANGLE;	//有没有人，用来控制是否锁定视角
	//按键控制
	bool bW, bS, bA, bD;
	bool bUp, bDown, bLeft, bRight;
	bool bBlank;
};

#endif