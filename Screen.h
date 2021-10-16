#pragma once

#include "GameObject.h"
#include "game.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

class Game;


class Screen {
public:
	double xpos, ypos;

	virtual void drawScreen(Game* g){}
	virtual void updateScreen(Game* g){}
	void getCursorPosition(Game* g);

	//help
	void screenToWorldCord();
	bool collisionBB(Game* g, GameObject* GO);

};

class ScreenHandler : public Screen {
public:
	enum SCREENTYPE { GAME, PAUSE, MAIN };
	SCREENTYPE screen;

	//----------------DEBUG VARIABLES----------------
	bool renderDebugScreen = false;
	std::string currentDebugObj;
	//----------------DEBUG VARIABLES----------------

	void ScreenInit(Game* g);
	void ScreenSwitch(SCREENTYPE screen, Game* g);
};

class PauseMenu : public Screen {
public:
	float spaceX = 100.0f;
	void drawScreen(Game* g) override;
	void updateScreen(Game* g) override;
	void remove(Game* g);
};

class MainMenu : public Screen {
public:
	void drawScreen(Game* g) override;
	//void updateScreen(Game* g) override;
	void remove(Game* g);
};

class GameScene : public Screen {
public:
	void drawScreen(Game* g) override;
	void updateScreen(Game* g) override;
	void remove(Game* g);
};