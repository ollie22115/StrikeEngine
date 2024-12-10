#pragma once

#include <string>

#include "Scene.h"

//the engine that handles rendering graphics to the screen
class SceneRenderer {
	//TODO!!!
public:
	SceneRenderer();

	bool loadScene(Scene* scene);

	void drawScene();

	inline Program& getProgram() { return program; }

	~SceneRenderer();

private:
	Scene* scene;
	VertexBuffer vb;
	IndexBuffer ib;
	Program program;
};