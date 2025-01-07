#pragma once

#include <string>

#include <Buffer.h>
#include <Program.h>
#include <Texture.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "../Scene.h"

struct RenderableObjectData {
	RenderableObject* object;
	int32_t size;
	int32_t offset;
	uint32_t textureID;

	inline RenderableObjectData(RenderableObject* object, int32_t size, int32_t offset, uint32_t textureID) : object(object), size(size), offset(offset), textureID(textureID) {}
};

//engine that handles rendering graphics to the screen
class SceneRenderer {
	//TODO!!!
public:
	SceneRenderer(GLFWwindow** window);

	bool loadScene(const Scene* scene);

	void drawScene(GLFWwindow* window);

	inline Program& getProgram() { return program; }

	~SceneRenderer() = default;

private:
	Scene* scene;
	VertexBuffer vb;
	IndexBuffer ib;
	Program program;
};