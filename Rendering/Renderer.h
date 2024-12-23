#pragma once

#include <string>

#include "Scene.h"

struct RenderableObject {
	Object* object;
	int32_t size;
	int32_t offset;
	uint32_t textureID;

	inline RenderableObject(Object* object, int32_t size, int32_t offset, uint32_t textureID) : object(object), size(size), offset(offset), textureID(textureID) {}
};

/*
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
*/