#pragma once

#include "../RenderingEngine/Scene.h"
#include "../Core/Input.h"
#include "../Combat/Combat.h"

//the interface controller for combat
class CombatInterface {
	//TODO!!!
public:
	CombatInterface(Combat combat);

	void onUpdate(const KeyCode& userInput);
	void onRender();

	~CombatInterface();

private:
	Scene combatScene;

	static Scene& genCombatScene(const Combat& combat);
};