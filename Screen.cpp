#include "Screen.h"

#define VEC3_ZERO glm::vec3(0.0f)

void Screen::getCursorPosition(Game* g) {
	glfwGetCursorPos(g->gameWindow, &xpos, &ypos);
}

void Screen::screenToWorldCord() {
	float x = ((2.0f * xpos) / 1920 - 1.0f) * 100.0;
	float y = (1.0f - (2.0f * ypos) / 1080) * 100.0;
	
	xpos = x;
	ypos = y;
}

bool Screen::collisionBB(Game* g, GameObject* GO) {
	if (xpos <= GO->boundingBox.x && xpos >= GO->boundingBox.y && ypos <= GO->boundingBox.z && ypos >= GO->boundingBox.w) {
		return true;
	}
	else {
		return false;
	}
}
void ScreenHandler::ScreenInit(Game* g) {
	if (screen == PAUSE) {
		Screen* crntMenu = new PauseMenu();

		g->ScreenObject.push_back(crntMenu);
	}

	if (screen == MAIN) {
		Screen* crntMenu = new MainMenu();

		g->ScreenObject.push_back(crntMenu);
	}

	if (screen == GAME) {
		Screen* crntMenu = new GameScene();

		g->ScreenObject.push_back(crntMenu);
	}
}

void ScreenHandler::ScreenSwitch(SCREENTYPE screen, Game* g) {
	this->screen = screen;

	if (screen == PAUSE) {
		g->pause = true;
	}

	if (screen == MAIN) {
		g->pause = true;
	}

	if (screen == GAME) {
		g->pause = false;
	}
}


void PauseMenu::drawScreen(Game* g) {
	g->shaders[2]->Activate();

	int w, h;
	glfwGetWindowSize(g->gameWindow, &w, &h);
	glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	g->fonts[1]->drawString(750.0f, 150.0f, "PAUSED", g->shaders[2]);
	g->fonts[1]->drawString(100.0f, 350.0f, "CONTINUE", g->shaders[2]);
	g->fonts[1]->drawString(100.0f, 550.0f, "OPTIONS", g->shaders[2]);
	g->fonts[1]->drawString(100.0f, 850.0f, "EXIT", g->shaders[2]);
}

void PauseMenu::updateScreen(Game* g) {
	int state = glfwGetMouseButton(g->gameWindow, GLFW_MOUSE_BUTTON_LEFT);

	if (glfwGetKey(g->gameWindow, GLFW_KEY_P) == GLFW_PRESS) {
		remove(g);
		g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::GAME, g);
		g->ScreenHandler[0]->ScreenInit(g);
	}

	if (state == GLFW_PRESS)
	{
		g->ScreenObject[0]->getCursorPosition(g);
		cout << g->ScreenObject[0]->ypos << endl;

		if (g->ScreenObject[0]->xpos <= 650.0 && g->ScreenObject[0]->xpos >= 96.0 && g->ScreenObject[0]->ypos >= 272.0 && g->ScreenObject[0]->ypos <= 357.0) {
			remove(g);
			g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::GAME, g);
			g->ScreenHandler[0]->ScreenInit(g);

			g->pause = false;
		}

		if (g->ScreenObject[0]->xpos <= 379.0 && g->ScreenObject[0]->xpos >= 96.0 && g->ScreenObject[0]->ypos >= 760.0 && g->ScreenObject[0]->ypos <= 860.0) {
			remove(g);
			g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::MAIN, g);
			g->ScreenHandler[0]->ScreenInit(g);

		}
	}

		
	
}

void PauseMenu::remove(Game* g) {
	g->removeScreen(this);
}

void MainMenu::drawScreen(Game* g) {
	g->shaders[2]->Activate();

	int w, h;
	glfwGetWindowSize(g->gameWindow, &w, &h);
	glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	g->fonts[1]->drawString(600.0f, 150.0f, "PONGCHAMP!", g->shaders[2]);
	g->fonts[1]->drawString(100.0f, 350.0f, "PLAY", g->shaders[2]);

}

void MainMenu::remove(Game* g) {
	g->removeScreen(this);
}

void GameScene::drawScreen(Game* g) {
	if (!g->pause || g->framestep > 0) {
		g->update();
		if (g->framestep > 0)
			g->framestep--;
	}

	
	//Exporting data & Render
	g->draw();
	//-----------------------------------------------------------------
	g->cameras[0]->updateMatrix(45.0f, 0.0f, 500.0f);

	//------------------------TEXT (NOTE: IMPLEMENT IN G.DRAW())----------------------------------------
	g->shaders[2]->Activate();



	int w, h;
	glfwGetWindowSize(g->gameWindow, &w, &h);
	glm::mat4 orthoP = roml::createOrto(0.0f, (float)w, (float)h, 0.0f);
	glUniformMatrix4fv(glGetUniformLocation(g->shaders[2]->ID, "ModViewProj"), 1, GL_FALSE, &orthoP[0][0]);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	g->texts[0]->update(g, g->gameWindow);
	g->texts[1]->update(g, g->gameWindow);

	g->fonts[0]->drawString(g->texts[0]->pos.x, g->texts[0]->pos.y, g->texts[0]->text, g->shaders[2]);
	g->fonts[0]->drawString(g->texts[1]->pos.x, g->texts[1]->pos.y, g->texts[1]->text, g->shaders[2]);

	//--------------DEBUG----------------------------
	g->debugGUI[0]->onClickDebug(g);

	g->debugGUI[0]->createDebugMenu(g);

	if (g->ScreenHandler[0]->renderDebugScreen) {
		g->debugGUI[0]->createDebugMenu(g->OBJList[0], g->ScreenHandler[0]->currentDebugObj, glm::vec3(-0.75f, 0.0f, 0.0f), VEC3_ZERO, glm::vec3(0.015f, 0.2f, 1.0f));
	}


}

void GameScene::updateScreen(Game* g) {
	if (glfwGetKey(g->gameWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		remove(g);
		g->ScreenHandler[0]->ScreenSwitch(ScreenHandler::SCREENTYPE::PAUSE, g);
		g->ScreenHandler[0]->ScreenInit(g);

		g->pause = true;
	}
}

void GameScene::remove(Game* g) {
	g->removeScreen(this);
}
