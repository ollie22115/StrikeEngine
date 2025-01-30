#pragma once

#include <string>

#include <Buffer.h>
#include <Program.h>
#include <Texture.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <unordered_map>

#include "../Scene.h"

namespace Strike {

	//engine that handles rendering graphics to the screen
	class GLRenderer {
		//TODO!!!
	public:
		GLRenderer(GLFWwindow** window);

		bool loadScene(Scene* scene);

		void drawScene(GLFWwindow* window);

		inline GLP::Program& getProgram() { return program; }

		~GLRenderer();

	private:
		struct GLObject {
			RenderableObject* object;
			int32_t vertexCount;
			int32_t offset;
			uint32_t textureID;

			GLObject() = default;
			inline GLObject(RenderableObject* object, int32_t size, int32_t offset, uint32_t textureID) : object(object), vertexCount(size), offset(offset), textureID(textureID) {}
		};

		Scene* scene;
		GLP::Program program;
		GLP::VertexBuffer vb;
		GLP::IndexBuffer ib;
		std::unordered_map<GLuint, GLP::Texture*> textureMap;
		std::vector<GLObject> rendererObjects;
	};

}