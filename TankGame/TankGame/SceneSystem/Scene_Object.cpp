#include "Scene_Object.h"

Scene_Object::Scene_Object()
:radius(0){
	pos[0] = pos[1] = pos[2] = 0;
}

Scene_Object::Scene_Object(double x, double y, double z)
:radius(0){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

Scene_Object::Scene_Object(point pt)
:radius(0){
	pos[0] = pt[0];
	pos[1] = pt[1];
	pos[2] = pt[2];
}

Scene_Object::~Scene_Object(){

}

double Scene_Object::getRadius() const{
	return radius;
}

point& Scene_Object::getPos(){
	return pos;
}