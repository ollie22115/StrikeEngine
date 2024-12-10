#pragma once

#include "../RenderingEngine/Scene.h"

//the controller for the main menu interface
class MainMenuInterface {
	//TODO!!!
public:
	MainMenuInterface();

	void onUpdate(KeyCode userInput);

	~MainMenuInterface();

private:
	Scene mainMenuScene;

	static Scene& genMainMenuScene();
};