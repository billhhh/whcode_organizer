#ifndef _H_SCENE_MANAGER_H
#define _H_SCENE_MANAGER_H

#include "Scene_Object_Land.h"
#include <vector>

class Scene_Manager{
private:
	Scene_Manager();
	static Scene_Manager* instance;

	std::vector<Scene_Object*> objectVec;
	int ObjectSum;

	static const int SCENE_WIDTH = 200;
	static const int SCENE_HEIGHT = 200;

public:
	static Scene_Manager* getInstance();
	~Scene_Manager();

	void init();
	std::vector<Scene_Object*>& getObjectVec();
	int getObjectSum() const;
	static const int getSceneWidth();
	static const int getSceneHeight();

	bool addObject(Scene_Object*);
	bool destroyAllObject();
	void drawObject();
	void draw();
};

#endif