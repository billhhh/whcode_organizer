#ifndef _H_SHELL_CAI_H_
#define _H_SHELL_CAI_H_

#include "../BaseDefine.h"

class Shell{
private:
	point startPos;
	point nextPos;
	double pit;
	double yaw;
	double speed;
	double dx;
	double dy;
	double dz;
	double rad;
	double radiusCollision;

	bool bStatus;

public:
	Shell(point& );
	~Shell();
	point &getStartPos();
	point &getNextPos();
	void setNextPos(point &);
	void draw();
	void setState(double speed,double yaw,double pit);
	void move();
	void setRad(double dRad);
	double getRad() const;
	void setRadCollision(double rc);
	double getRadCollision() const;
	void unMove();

	void setStatus(bool val);
	bool getStatus() const;
};
#endif