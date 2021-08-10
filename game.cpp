
#include "game.h"

Game::Game() {
	lastTime = glfwGetTime();
	this->gameWindow = gameWindow;
}

void Game::deleteObj(GameObject* GO) {	
	for (auto c = gameObjects.begin(); c != gameObjects.end(); c++) {
		if (*c == GO)
		{
			delete GO;
			gameObjects.erase(c);
			return;
		}
	}
}
void Game::update() {
	deltaTime = (float)glfwGetTime() - lastTime;
	lastTime = (float)glfwGetTime();
	for (GameObject* o : gameObjects)
		if (o != nullptr)
			o->update(this);

	for (GameObject* p : particleSystems)
		p->update(this);


	
}

void Game::draw() {
	for (GameObject* o : gameObjects)
		if (o != nullptr)
			o->draw(this);
}