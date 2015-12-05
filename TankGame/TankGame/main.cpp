
#include "Game_System.h"

void main(int argc, char** argv){
	GameSystem* gameSystem;
	gameSystem->setWindow(800, 600);
	gameSystem->getInstance()->GameInit(argc, argv);
}
