#pragma once

#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>
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

		void loadScene(std::shared_ptr<Scene>& scene);

		void update() override;

		void draw(std::shared_ptr<Window>& window, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;


		//OpenGL specific functions
		void uploadUniform4f(const char* uniformName, glm::vec4 vector4f);
		void uploadUniformMat4f(const char* uniformName, glm::mat4 mat4f);

		//~GLRenderer() override;

	private:
		struct GLMesh {
			Object* object;	//TODO change to shared pointer at some point
			GLMaterial material;
			int32_t vertexCount;
			int32_t offset;

			GLMesh() = default;
			inline GLMesh(Object* object, const GLMaterial& material, int32_t vertexCount, int32_t offset) : 
				object(object), material(material), vertexCount(vertexCount), offset(offset) {}
		};

		Scene* scene;
		std::unique_ptr<GLVertexBuffer> vertexBufferStatic;
		std::unique_ptr<GLVertexBuffer> vertexBufferDynamic;
		std::unique_ptr<GLIndexBuffer> indexBufferStatic;
		std::unique_ptr<GLIndexBuffer> indexBufferDynamic;

		std::unordered_map<std::string, std::shared_ptr<GLProgram>> shaderLibrary;
		std::unordered_map<std::string, std::shared_ptr<GLTexture2D>> textureLibrary;

		std::vector<GLMesh> rendererObjectsStatic;
		std::vector<GLMesh> rendererObjectsDynamic;

		std::shared_ptr<GLTexture2D> loadTexture2D(const std::string& filePath);
		std::shared_ptr<GLProgram> loadShader(const std::string& filePath);

		//TODO!!! figure out what to do with vertex arrays
		GLuint staticVertexArrayID;
		GLuint dynamicVertexArrayID;
	};

}