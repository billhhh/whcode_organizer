#ifndef _H_TANK_MANAGER_H
#define _H_TANK_MANAGER_H

#include "Tank_Controller.h"
#include "Tank_Model_TypeA.h"
#include "Tank_Model_TypeB.h"
#include "Tank_Model_TypeC.h"
#include <vector>

class Tank_Manager{
private:
	Tank_Manager();
	static Tank_Manager* instance;

	std::vector<Tank_Controller*> tankVec;
	int tankSum;
	int tankWorking;

public:
	static Tank_Manager* getInstance();
	~Tank_Manager();

	void init();
	void init(std::vector<point3>& vec);
	std::vector<Tank_Controller*>& getTankVec();
	Tank_Controller* getTankWorking();
	void setTankWorking(int i);
	int getTankWorkingNum() const;
	int getTankSum() const;
	void clearShell();
	void reStart();
	void draw();
}; 

#endif