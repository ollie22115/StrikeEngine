#include "StrikePCH.h"
#include "GLRenderer.h"
#include "GLFW/GLFWWindow.h"

#include "Utils/FileLoader.h"
#include "Scene/Scene.h"
#include "Scene/Component/RenderableComponent.h"

#ifdef STRIKE_DEBUG
#include "Debugging/StrikeDebug.h"
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

		//TODO!!! Figure out what to do with vertex arrays
		GLuint vertexArrayID;
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);
	}

	void GLRenderer::swapBuffers(const std::shared_ptr<Window>& window) {
#if defined(STRIKE_GLFW)
		glfwSwapBuffers(((GLFWWindow*)window.get())->getGLFWWindowHandle());
#else
		STRIKE_ASSERT(false, LOG_PLATFORM_OPENGL, "Window Platform not supported!");
#endif
	}

	void GLRenderer::loadScene(std::shared_ptr<Scene>& scene) {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		for (Object& object : scene->getObjects()) {
			std::vector<std::shared_ptr<RenderableComponent>> renderables = object.getRenderableComponents();
			if (renderables.empty()) continue;

			for (std::shared_ptr<RenderableComponent>& renderable : renderables) {
				std::vector<Vertex> objectVertices =  renderable->getVertices(object.transform);
				
				Object* meshBaseObjectPtr = &object;
				size_t meshVertexCount = objectVertices.size();
				size_t meshOffset = indices.size();

				for (Vertex& objectVertex : objectVertices) {
					int32_t index = -1;

					for (int i = 0; i < vertices.size(); i++) if (vertices[i] == objectVertex) {
						index = i;
						break;
					}

					if (index < 0) {
						vertices.push_back(objectVertex);
						index = (int32_t) vertices.size() - 1;
					}

					indices.push_back(index);
				}

				const Material& coreMaterial = renderable->getMaterial();
				GLMaterial meshMaterial(loadShader(coreMaterial.shaderPath), loadTexture2D(coreMaterial.texturePath));

				rendererObjectsStatic.emplace_back(meshBaseObjectPtr, meshMaterial, meshVertexCount, meshOffset);
			}
		}

		vertexBufferStatic->setVertexLayout(Vertex::getLayout());

		if(!vertices.empty())
			vertexBufferStatic->setData((uint32_t) vertices.size() * Vertex::getLayout().size(), &vertices[0], GL_STATIC_DRAW);
		if(!indices.empty())
			indexBufferStatic->setData((uint32_t) indices.size() * 4, &indices[0], GL_STATIC_DRAW);
	}

	void GLRenderer::update() {
		//TODO!!! for now method will only update dynamic vertex buffer

	}

	void GLRenderer::draw(std::shared_ptr<Window>& window) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		vertexBufferStatic->bind();
		indexBufferStatic->bind();
		
		for (GLMesh& mesh : rendererObjectsStatic) {
			if (!mesh.object->isVisible) continue;

			mesh.material.bind();
			glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, (const void*) (mesh.offset * sizeof(float)));
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
