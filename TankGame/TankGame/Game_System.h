#ifndef _H_GAMESYSTEM_
#define _H_GAMESYSTEM_

#include <stdlib.h>
#include <stdio.h>
#include <glaux.h>
#include "Global.h"
#include "Control_System.h"

#define MAXHITS 200

//视角相关
struct Camera{
	GLfloat camX;
	GLfloat camY;
	GLfloat camZ;
};

struct MouseView{
	int mx;
	int my;
	int mdown;
	int buttonDown;
};

class GameSystem{
protected:
	static GameSystem* instance;
	GameSystem();

	static GLfloat angle;
	static int preSystemTime;
	static int nowSystemTime;
	static int shellFlySystemTime;
	static int shellDspSystemTime;

	static int windowWidth;
	static int windowHeight;

public:
	//视角相关
	static MouseView mouseView;
	static Camera cam;
	static Camera camPos;
	static bool bView;

	static GLfloat camPitch;
	static GLfloat camYaw;
	static GLfloat camRadius;

	//拾取相关
	static GLint windW;
	static GLint windH;
	static GLuint selectBuf[MAXHITS];
	static GLint hits;
	static GLint vp[4];

	static Control_System* control_system;
private:
	static AUX_RGBImageRec* LoadBMP(char *Filename);
	static void getView();
	static void setTexture();

public:
	static GameSystem* getInstance();
	~GameSystem();
	bool GameInit(int argc, char** argv);
	
	static void display(void);
	static void reshape(int,int);
	static void motion(int x, int y) ;
	static void mouse(int button, int state, int x, int y);
	static void keyboard(unsigned char key,int x,int y);
	static void keyboardUp(unsigned char key,int x,int y);
	static void specialKey(int key, int x, int y);
	static void specialKeyUp(int key, int x, int y);
	static void idle();
	static void doMyInit(void);
	static void mainMenu(int input);
	static void selectTankMenu(int input);
	static bool DoSelect(GLint x, GLint y);

	static void controlFrameAndRedisplay();

	static void setWindow(int w, int h);
};	

#endif