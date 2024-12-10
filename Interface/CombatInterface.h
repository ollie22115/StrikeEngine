#pragma once

#include "../RenderingEngine/Scene.h"

//the interface controller for combat
class CombatInterface {
	//TODO!!!
public:
	CombatInterface(Combat combat);

	void onUpdate(KeyCode userInput);
	void onRender();

	~CombatInterface();

private:
	Scene combatScene;

	static Scene& genCombatScene(const Combat& combat);
};