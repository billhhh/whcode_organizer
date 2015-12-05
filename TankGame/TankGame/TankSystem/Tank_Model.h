#ifndef _H_TANK_MODEL_H
#define _H_TANK_MODEL_H

#include "../BaseDefine.h"


//纯虚类
class Tank_Model{
public:
	Tank_Model();
	virtual ~Tank_Model();
	virtual void init() = 0;   //两个纯虚函数，方便继承
	virtual void draw() = 0;
	void setAngOri(double ang);
	void setAngPos(double ang);
	void setAngBtyUD(double ang);
	void setAngBtyLR(double ang);

	double getPower() const;
	double getRadius() const;
public:
	double power;
	double width;
	double length;
	double radius;

	double height;//炮台高度
	double gHeight;//炮管高度

	double angOri;	//初始方向
	double angPos;	//坦克与初始正方向所形成的角度  //+z为起始方向
	double angBtyUD;
	double angBtyLR;
};

#endif