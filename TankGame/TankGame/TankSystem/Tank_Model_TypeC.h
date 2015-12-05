#ifndef _H_TANK_MODEL_TYPEC_H
#define _H_TANK_MODEL_TYPEC_H

#include "Tank_Model.h"

class Tank_Model_TypeC:public Tank_Model{
private:
	GLUquadric *pObj1,*pObj2;
public:
	Tank_Model_TypeC();
	Tank_Model_TypeC(point& oriPos);
	virtual ~Tank_Model_TypeC();

	void wheel();
	void body();
	void guntower();

	virtual void init();
	virtual void draw();
};

#endif