#ifndef _H_TANK_MODEL_TYPEB_H
#define _H_TANK_MODEL_TYPEB_H

#include "Tank_Model.h"

class Tank_Model_TypeB:public Tank_Model{
private:
	GLUquadric *SP,*LG,*RG,*LG2,*RG2;
public:
	Tank_Model_TypeB();
	Tank_Model_TypeB(point& oriPos);
	virtual ~Tank_Model_TypeB();

	void track_L(void);//左边履带
	void track_R(void);//右边履带
	void body(void);//车身
	void bettery(void);//炮台
	void ball(void);//画球
	void gun(void);//炮管

	virtual void init();
	virtual void draw();
};

#endif