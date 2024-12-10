#pragma once

#include <string>

#include "Scene.h"

//the engine that handles rendering graphics to the screen
class RenderingEngine {
	//TODO!!!
public:
	RenderingEngine();

	bool loadScene();

	void onDraw();

	void setUniformf(const std::string& uniformName, float value);

private:
	Scene* scene;
	VertexBuffer vb;
	IndexBuffer ib;
	Program program;
};