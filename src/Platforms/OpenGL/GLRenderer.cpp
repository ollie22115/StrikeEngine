#include "StrikePCH.h"
#include "GLRenderer.h"
#include "GLFW/GLFWWindow.h"

#include "Utils/FileLoader.h"
#include "Scene/Scene.h"
#include "Scene/Component/RenderableComponent.h"

#ifdef STRIKE_DEBUG
#include "Debugging/StrikeDebug.h"
#include "GLDebug.h"
#endif

namespace Strike {

	//public Methods
	void GLRenderer::init(const std::shared_ptr<Window>& window) {

#if defined(STRIKE_GLFW)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwMakeContextCurrent(((GLFWWindow*)window.get())->getGLFWWindowHandle());
#else
		STRIKE_ASSERT(false, LOG_PLATFORM_OPENGL, "Window Platform not supported!");
#endif

		int gladLoadResult = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		STRIKE_ASSERT(gladLoadResult, LOG_PLATFORM_OPENGL, "Failed to initialize GLAD!");

		vertexBufferStatic = std::make_unique<GLVertexBuffer>();
		vertexBufferDynamic = std::make_unique<GLVertexBuffer>();
		indexBufferStatic = std::make_unique<GLIndexBuffer>();
		indexBufferDynamic = std::make_unique<GLIndexBuffer>();

		glViewport(0, 0, window->getWidth(), window->getHeight());

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		textureLibrary["Default"] = std::make_shared<GLTexture2D>();

		//TODO!!! Figure out what to do with vertex arrays
		glGenVertexArrays(1, &staticVertexArrayID);
		glGenVertexArrays(1, &dynamicVertexArrayID);
	}

	void GLRenderer::swapBuffers(const std::shared_ptr<Window>& window) {
#if defined(STRIKE_GLFW)
		glfwSwapBuffers(((GLFWWindow*)window.get())->getGLFWWindowHandle());
#else
		STRIKE_ASSERT(false, LOG_PLATFORM_OPENGL, "Window Platform not supported!");
#endif
	}

	void GLRenderer::loadScene(std::shared_ptr<Scene>& scene) {
		std::vector<Vertex> staticVertices;
		std::vector<uint32_t> staticIndices;

		std::vector<Vertex> dynamicVertices;
		std::vector<uint32_t> dynamicIndices;

		for (std::shared_ptr<Object>& object : scene->getObjects()) {

			Renderable renderable = object->getRenderable();
			if(!renderable.isRenderable())
				continue;

			if (object->isStatic()) {
				std::vector<Vertex>& objectVertices = renderable.getVertices();

				Object* meshBaseObjectPtr = object.get();
				size_t meshVertexCount = objectVertices.size();
				size_t meshOffset = staticIndices.size();

				for (Vertex& objectVertex : objectVertices) {
					int32_t index = -1;

					for (int i = 0; i < staticVertices.size(); i++) if (staticVertices[i] == objectVertex) {
						index = i;
						break;
					}

					if (index < 0) {
						staticVertices.push_back(objectVertex);
						index = (int32_t)staticVertices.size() - 1;
					}

					staticIndices.push_back(index);
				}

				const Material& coreMaterial = renderable.getMaterial();
				GLMaterial meshMaterial(loadShader(coreMaterial.shaderPath), loadTexture2D(coreMaterial.texturePath));

				rendererObjectsStatic.emplace_back(meshBaseObjectPtr, meshMaterial, meshVertexCount, meshOffset);

			} else {
				std::vector<Vertex>& objectVertices = renderable.getVertices();

				Object* meshBaseObjectPtr = object.get();
				size_t meshVertexCount = objectVertices.size();
				size_t meshOffset = dynamicIndices.size();

				for (Vertex& objectVertex : objectVertices) {
					int32_t index = -1;

					for (int i = 0; i < dynamicVertices.size(); i++) if (dynamicVertices[i] == objectVertex) {
						index = i;
						break;
					}

					if (index < 0) {
						dynamicVertices.push_back(objectVertex);
						index = (int32_t)dynamicVertices.size() - 1;
					}

					dynamicIndices.push_back(index);
				}

				const Material& coreMaterial = renderable.getMaterial();
				GLMaterial meshMaterial(loadShader(coreMaterial.shaderPath), loadTexture2D(coreMaterial.texturePath));

				rendererObjectsDynamic.emplace_back(meshBaseObjectPtr, meshMaterial, meshVertexCount, meshOffset);
			}
		}

		//TODO!!! FIX the following When you figure out what to do with vertex arrays
		glBindVertexArray(staticVertexArrayID);
		vertexBufferStatic->bind();
		indexBufferStatic->bind();
		vertexBufferStatic->setVertexLayout(Vertex::getLayout());

		if (!staticVertices.empty())
			vertexBufferStatic->setData((uint32_t)staticVertices.size() * Vertex::getLayout().size(), &staticVertices[0], GL_STATIC_DRAW);
		if (!staticIndices.empty())
			indexBufferStatic->setData((uint32_t)staticIndices.size() * 4, &staticIndices[0], GL_STATIC_DRAW);

		glBindVertexArray(dynamicVertexArrayID);
		vertexBufferDynamic->bind();
		indexBufferDynamic->bind();
		vertexBufferDynamic->setVertexLayout(Vertex::getLayout());

		if (!dynamicVertices.empty())
			vertexBufferDynamic->setData((uint32_t)dynamicVertices.size() * Vertex::getLayout().size(), &dynamicVertices[0], GL_DYNAMIC_DRAW);
		if (!dynamicIndices.empty())
			indexBufferDynamic->setData((uint32_t)dynamicIndices.size() * 4, &dynamicIndices[0], GL_DYNAMIC_DRAW);
	}

	void GLRenderer::update() {
		//TODO!!! for now method will only update dynamic vertex buffer
		glBindVertexArray(dynamicVertexArrayID);
		vertexBufferDynamic->bind();
		indexBufferDynamic->bind();

		std::vector<Vertex> dynamicVertices;
		std::vector<uint32_t> dynamicIndices;

		for (GLMesh& mesh : rendererObjectsDynamic) {
			Object& coreObject = *mesh.object;
			
			Renderable renderable = coreObject.getRenderable();
			if (!renderable.isRenderable())
				continue;

			std::vector<Vertex> objectVertices = renderable.getVertices();

			for (Vertex& objectVertex : objectVertices) {
				int32_t index = -1;

				for (int i = 0; i < dynamicVertices.size(); i++) if (dynamicVertices[i] == objectVertex) {
					index = i;
					break;
				}

				if (index < 0) {
					dynamicVertices.push_back(objectVertex);
					index = (int32_t)dynamicVertices.size() - 1;
				}

				dynamicIndices.push_back(index);
			}
		}

		if(!dynamicVertices.empty())
			glBufferSubData(GL_ARRAY_BUFFER, 0, dynamicVertices.size() * Vertex::getLayout().size(), &dynamicVertices[0]);
		if (!dynamicIndices.empty())
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, dynamicIndices.size() * sizeof(uint32_t), &dynamicIndices[0]);
	}

	void GLRenderer::draw(std::shared_ptr<Window>& window, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO!!! Fix Temporary line of Code
		glBindVertexArray(staticVertexArrayID);
		
		for (GLMesh& mesh : rendererObjectsStatic) {
			if (!mesh.object->isVisible()) 
				continue;

			mesh.material.bind(viewMatrix, projectionMatrix);
			glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, (const void*) (mesh.offset * sizeof(uint32_t)));
		}

		//TODO!!! Fix Temporary line of Code
		glBindVertexArray(dynamicVertexArrayID);

		for (GLMesh& mesh : rendererObjectsDynamic) {
			if (!mesh.object->isVisible())
				continue;

			mesh.material.bind(viewMatrix, projectionMatrix);
			glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, (const void*)(mesh.offset * sizeof(uint32_t)));
		}

		swapBuffers(window);
	}

	/*
	GLRenderer::~GLRenderer() {
		//TODO!!!

	}
	*/



	//PRIVATE METHODS
	std::shared_ptr<GLTexture2D> GLRenderer::loadTexture2D(const std::string& filePath) {
		if(textureLibrary.find(filePath) == textureLibrary.end())
			textureLibrary[filePath] = std::make_shared<GLTexture2D>(filePath.c_str());

		return textureLibrary[filePath];
	}

	std::shared_ptr<GLProgram> GLRenderer::loadShader(const std::string& shaderPath) {
		if (shaderLibrary.find(shaderPath) == shaderLibrary.end()) {
			std::string src = FileLoader::loadTextFile(shaderPath);

			shaderLibrary[shaderPath] = std::make_shared<GLProgram>();
			shaderLibrary[shaderPath]->compile(src);
		}

		return shaderLibrary[shaderPath];
	}
}
