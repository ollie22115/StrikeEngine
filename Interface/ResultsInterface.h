#pragma once

#include "../RenderingEngine/Scene.h"

//controller for the results screen interface
class ResultsInterface {
	//TODO!!!
public:
	ResultsInterface();

	void onUpdate(KeyCode userInput);

	~ResultsInterface();

private:
	Scene resultsScene;

	static Scene& genResultsScene();
};