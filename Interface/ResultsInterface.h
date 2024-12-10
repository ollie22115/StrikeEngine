#pragma once

#include "../RenderingEngine/Scene.h"
#include "../Core/Input.h"

//controller for the results screen interface
class ResultsInterface {
	//TODO!!!
public:
	ResultsInterface();

	void onUpdate(const KeyCode& userInput);

	~ResultsInterface();

private:
	Scene resultsScene;

	static Scene& genResultsScene();
};