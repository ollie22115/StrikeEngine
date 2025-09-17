#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

#include "Rendering/Renderer.h"
#include "Scene/Object.h"
#include "GLProgram.h"
#include "GLBuffer.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLMaterial.h"

namespace Strike {

	//engine that handles rendering graphics to the screen
	class GLRenderer : public Renderer {
		//TODO!!!
	public:
		GLRenderer() = default;

		void init(const std::shared_ptr<Window>& window) override;

		void swapBuffers(const std::shared_ptr<Window>& window) override;

		void loadObject(std::shared_ptr<Object>& object) override;

		void update() override;

		void draw(std::shared_ptr<Window>& window, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;


		//OpenGL specific functions
		void uploadUniform4f(const char* uniformName, glm::vec4 vector4f);
		void uploadUniformMat4f(const char* uniformName, glm::mat4 mat4f);

		//~GLRenderer() override;

	private:

		struct GLMesh {
			Object* object;	//TODO change to shared pointer at some point
			ResourcePointer<Material> materialPtr;
			int32_t vertexCount;
			int32_t offset;

			GLMesh() = default;
			inline GLMesh(Object* object, const ResourcePointer<Material>& materialPtr, int32_t vertexCount, int32_t offset) : 
				object(object), materialPtr(materialPtr), vertexCount(vertexCount), offset(offset) {}
			
		};

		Scene* scene;
		std::unique_ptr<GLVertexBuffer> vertexBufferStatic;
		std::unique_ptr<GLVertexBuffer> vertexBufferDynamic;
		std::unique_ptr<GLIndexBuffer> indexBufferStatic;
		std::unique_ptr<GLIndexBuffer> indexBufferDynamic;

		std::vector<Vertex> staticVertices;
		std::vector<uint32_t> staticIndices;
		std::vector<Vertex> dynamicVertices;
		std::vector<uint32_t> dynamicIndices;

		std::vector<GLMesh> rendererObjectsStatic;
		std::vector<GLMesh> rendererObjectsDynamic;

		//TODO!!! figure out what to do with vertex arrays
		GLuint staticVertexArrayID;
		GLuint dynamicVertexArrayID;
	};

}