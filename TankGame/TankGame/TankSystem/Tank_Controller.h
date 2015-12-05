#ifndef _H_TANK_CONTROLLER_H
#define _H_TANK_CONTROLLER_H

#include "Tank_Model.h"
#include "Shell.h"

class Tank_Controller{
private:
	Tank_Model* tank;
	Shell* tank_shell;

	point prePos;			//前一个状态所在位置
	point nowPos;			//当前状态所在位置

	double angleOrigin;		//初始方向
	double anglePos;		//坦克与初始正方向所形成的角度  //+z为起始方向
	double speedMove;			//移动速度
	double speedTurn;			//转向速度	//角度为度量单位360

	double angleBetteryUD;		//炮台上下角度
	double angleBetteryLR;		//炮台左右角度
	double speedTurnBetteryUD;	//炮台转速
	double speedTurnBetteryLR;
	int		maxTurnUD;			//上下最大旋转角度10
	int		maxTurnLR;			//左右最大旋转角度

	double shell_speed;
	bool bStatus;

	char dirTank;
	char dirBettery;
public:
	Tank_Controller();
	Tank_Controller(point pos);
	~Tank_Controller();
	void init();
	void initTank(Tank_Model* tank);

	point& getPrePos();
	point& getNowPos();
	void setNowPos(point&);

	double &getAngleOrigin();
	double &getAnglePos();
	double &getAngleBetteryUD();
	double &getAngleBetteryLR();
	double getHeight();

	void move(unsigned int );			//整只坦克的移动
	void unMove();
	void turnBettery(unsigned int);		//炮台移动

	void fire();
	void unfire();
	void moveShell();
	void explosionShell();
	void setStatus(bool val);
	bool getStatus();
	point& getShellPos();
	double getCollisionRad();
	double getShellRad();
	bool isShellExist();

	//protected:
	void moveUp();
	void moveDown();
	void turnLeft();
	void turnRight();

	void turnUpBettery();
	void turnDownBettery();
	void turnLeftBettery();
	void turnRightBettery();

	void draw();

	void setDirTank(char);
	char getDirTank() const;
	void setDirBty(char);
	char getDirBty() const;
};

#endif