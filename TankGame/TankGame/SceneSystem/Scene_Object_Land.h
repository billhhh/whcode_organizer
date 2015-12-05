#ifndef _H_SCENE_OBJECT_LAND_H
#define _H_SCENE_OBJECT_LAND_H

#include "Scene_Object.h"

class Scene_Object_Land:public Scene_Object{
private:	
	point pos;
	GLUquadric *SP;
public:
	Scene_Object_Land();
	Scene_Object_Land(double x, double y, double z);
	Scene_Object_Land(point);
	virtual ~Scene_Object_Land();
	virtual void draw();
};

#endif