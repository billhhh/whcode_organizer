#include "Tank_Controller.h"

Tank_Controller::Tank_Controller(){
	init();
}

Tank_Controller::Tank_Controller(point pos){
	init();
	for(int i = 0; i < 3; ++i)
		prePos[i] = nowPos[i] = pos[i];
}


Tank_Controller::~Tank_Controller(){
	if( tank != NULL){
		delete tank;
		tank = NULL;
	}
	if( tank_shell != NULL){
		delete tank_shell;
		tank = NULL;
	}
}

void Tank_Controller::init(){
	for(int i = 0; i < 3 ; ++i)
		prePos[i] = nowPos[i] = 0;

	angleOrigin = 0;
	anglePos = 0;
	speedMove = 0.3;
	speedTurn = 0.4;

	angleBetteryLR = 0;
	angleBetteryUD = 0;
	speedTurnBetteryLR = 1;
	speedTurnBetteryUD = 0.2;

	maxTurnLR = 30;
	maxTurnUD = 10;

	tank = NULL;
	tank_shell = NULL;
	shell_speed = 7;

	bStatus = true;

	dirTank = 0;
	dirBettery = 0;
}

void Tank_Controller::initTank(Tank_Model* _tank){
	if( tank != NULL)
		delete tank;
	tank = _tank;
	
}

//位置相关函数
point& Tank_Controller::getPrePos(){
	return prePos;
}
point& Tank_Controller::getNowPos(){
	return nowPos;
}
void Tank_Controller::setNowPos(point& temP){
	for(int i = 0; i< 3; ++i)
		nowPos[i] = temP[i];
}
double& Tank_Controller::getAngleOrigin(){
	return angleOrigin;
}

double& Tank_Controller::getAnglePos(){
	return anglePos;
}

//坦克模型移动
void Tank_Controller::move(unsigned int key){
	switch(key){
	case 'w':	moveUp(); break;
	case 's':	moveDown();break;
	case 'a':	turnLeft();break;
	case 'd':	turnRight();break;
	}
}

void Tank_Controller::unMove(){
	for(int i = 0; i < 3; i++){
		nowPos[i] = prePos[i];
	}
}
void Tank_Controller::moveUp(){
	prePos[2] = nowPos[2];
	nowPos[2] += speedMove*cos(anglePos/360*2*PI);
	if(anglePos != 0){
		prePos[0] = nowPos[0];
		nowPos[0] += speedMove*sin(anglePos/360*2*PI);
	}
}

void Tank_Controller::moveDown(){
	prePos[2] = nowPos[2];
	nowPos[2] -= speedMove*cos(anglePos/360*2*PI);
	if(anglePos != 0){
		prePos[0] = nowPos[0];
		nowPos[0] -= speedMove*sin(anglePos/360*2*PI);
	}
}

void Tank_Controller::turnLeft(){
	if(0){
		prePos[0] = nowPos[0];
		nowPos[0] -= speedMove;
	}else{
		anglePos += speedTurn;
		if(anglePos > 360)
			anglePos -= 360;
	}
}

void Tank_Controller::turnRight(){
	if(0){
		prePos[0] = nowPos[0];
		nowPos[0] += speedMove;
	}else{
		anglePos -= speedTurn;
		if(anglePos < -360)
			anglePos += 360;
	}
}

//炮台转向
void Tank_Controller::turnBettery(unsigned int key){
	switch(key){
	case GLUT_KEY_UP:	turnUpBettery();break;
	case GLUT_KEY_DOWN:	turnDownBettery();break;
	case GLUT_KEY_LEFT:	turnLeftBettery();break;
	case GLUT_KEY_RIGHT:turnRightBettery();break;
	}
}

void Tank_Controller::turnUpBettery(){
	if(angleBetteryUD < maxTurnUD)
		angleBetteryUD += speedTurnBetteryUD;
}

void Tank_Controller::turnDownBettery(){
	if(angleBetteryUD > 0)
		angleBetteryUD -= speedTurnBetteryUD;
}

void Tank_Controller::turnLeftBettery(){
	if(angleBetteryLR < maxTurnLR)
		angleBetteryLR += speedTurnBetteryLR;
}

void Tank_Controller::turnRightBettery(){
	if(angleBetteryLR > -maxTurnLR)
		angleBetteryLR -= speedTurnBetteryLR;
}

double& Tank_Controller::getAngleBetteryLR(){
	return angleBetteryLR;
}

double& Tank_Controller::getAngleBetteryUD(){
	return angleBetteryUD;
}

//获得坦克高度
double Tank_Controller::getHeight(){
	return tank->height;
}

//坦克开炮
void Tank_Controller::fire(){
	if( tank_shell== NULL){
		point pos;
		pos[0] = nowPos[0];
		pos[1] = nowPos[1]+ tank->gHeight;
		pos[2] = nowPos[2];
		tank_shell = new Shell(pos);
		tank_shell->setState(shell_speed, (angleOrigin+anglePos+angleBetteryLR)*2*PI/360,(angleBetteryUD)*2*PI/360);
		tank_shell->setRadCollision(tank->power);
	}
}

void Tank_Controller::unfire(){
	if( tank_shell != NULL ){
		if( !tank_shell->getStatus()){
			delete tank_shell;
			tank_shell = NULL;
		}
	}
}

void Tank_Controller::moveShell(){
	if( tank_shell!= NULL){
		tank_shell->move();
		if( tank_shell->getNextPos()[1] <= 0){
			explosionShell();
		}
	}
}

void Tank_Controller::explosionShell(){
	tank_shell->setRad(tank->getPower());
	tank_shell->unMove();
	tank_shell->setStatus(false);
}

point& Tank_Controller::getShellPos(){
	return tank_shell->getNextPos();
}

void Tank_Controller::setStatus(bool val){
	bStatus = val;
}

bool Tank_Controller::getStatus(){
	return bStatus;
}

double Tank_Controller::getShellRad(){
	return tank_shell->getRad();
}

double Tank_Controller::getCollisionRad(){
	return tank->getRadius();
}

bool Tank_Controller::isShellExist(){
	if (tank_shell != NULL)
		return true;
	else
		return false;
}

void Tank_Controller::draw(){
	tank->setAngOri(angleOrigin);
	tank->setAngPos(anglePos);
	tank->setAngBtyUD(angleBetteryUD);
	tank->setAngBtyLR(angleBetteryLR);

	glPushMatrix();
	//************************
	glTranslatef(nowPos[0]-prePos[0],nowPos[1]-prePos[1],nowPos[2]-prePos[2]);
	glTranslatef(prePos[0],prePos[1],prePos[2]);
	//***************************
	tank->draw();

	glPopMatrix();
	if( tank_shell!= NULL){
		tank_shell->draw();
	}
}

void Tank_Controller::setDirTank(char c){
	dirTank = c;
}

char Tank_Controller::getDirTank() const{
	return dirTank;
}

void Tank_Controller::setDirBty(char c){
	dirBettery = c;
}

char Tank_Controller::getDirBty() const{
	return dirBettery;
}