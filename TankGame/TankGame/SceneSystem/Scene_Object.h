#ifndef _H_SCENE_OBJECT_H
#define _H_SCENE_OBJECT_H

#include "../BaseDefine.h"

class Scene_Object{
protected:
	double radius;
	point pos;

public:
	Scene_Object();
	Scene_Object(double x, double y, double z);
	Scene_Object(point );
	virtual ~Scene_Object();
	virtual void draw() = 0;
	double getRadius() const;
	point& getPos();
};

#endif