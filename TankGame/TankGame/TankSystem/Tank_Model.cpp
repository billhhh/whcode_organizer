#include "Tank_Model.h"

Tank_Model::Tank_Model(){
}

Tank_Model::~Tank_Model(){
}

void Tank_Model::setAngOri(double ang){
	angOri = ang;
}

void Tank_Model::setAngPos(double ang){
	angPos = ang;
}

void Tank_Model::setAngBtyUD(double ang){
	angBtyUD = ang;
}

void Tank_Model::setAngBtyLR(double ang){
	angBtyLR = ang;
}

double Tank_Model::getPower() const{
	return power;
}

double Tank_Model::getRadius() const{
	return radius;
}