#pragma once

#include "../RenderingEngine/Scene.h"
#include "../Core/Input.h"

//the controller for the main menu interface
class MainMenuInterface {
	//TODO!!!
public:
	MainMenuInterface();

	void onUpdate(const KeyCode& userInput);

	~MainMenuInterface();

private:
	Scene mainMenuScene;

	static Scene& genMainMenuScene();
};