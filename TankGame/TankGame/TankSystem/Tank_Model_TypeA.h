#ifndef _H_TANK_MODEL_TYPEA_H
#define _H_TANK_MODEL_TYPEA_H

#include "Tank_Model.h"

class Tank_Model_TypeA:public Tank_Model{
private:
	GLUquadric *pObj1,*pObj2,*pObj3,*pObj4;
public:
	Tank_Model_TypeA();
	Tank_Model_TypeA(point& oriPos);
	virtual ~Tank_Model_TypeA();

	void tank();
	void shaft();
	void track();
	void track2(int f);
	void bettery();
	virtual void init();
	virtual void draw();
};

#endif