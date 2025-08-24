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

		//TODO!!! Figure out what to do with vertex arrays
		glGenVertexArrays(1, &staticVertexArrayID);
		glGenVertexArrays(1, &dynamicVertexArrayID);
	}

	void GLRenderer::swapBuffers(const std::shared_ptr<Window>& window) {
		window->swapBuffers();
	}

	void GLRenderer::loadObject(std::shared_ptr<Object>& object) {
		STRIKE_ASSERT(object->isRenderable(), LOG_PLATFORM_OPENGL, 
			"object must have a renderable component to be loaded into the Renderer!");

		std::vector<Vertex>& vertices = (object->isStatic()) ? staticVertices : dynamicVertices;
		std::vector<uint32_t>& indices = (object->isStatic()) ? staticIndices : dynamicIndices;

		Renderable renderable = object->getRenderable();

		std::vector<Vertex>& objectVertices = renderable.getVertices();

		Object* meshBaseObjectPtr = object.get();
		size_t meshVertexCount = objectVertices.size();
		size_t meshOffset = indices.size();

		for (Vertex& objectVertex : objectVertices) {
			int32_t index = -1;

			for (int i = 0; i < vertices.size(); i++) 
				if (vertices[i] == objectVertex) {
					index = i;
					break;
			}

			if (index < 0) {
				vertices.push_back(objectVertex);
				index = (int32_t)vertices.size() - 1;
			}

			indices.push_back(index);
		}

		GLMaterial meshMaterial(renderable.shaderHandle, renderable.textureHandle);

		if(object->isStatic())
			rendererObjectsStatic.emplace_back(meshBaseObjectPtr, meshMaterial, meshVertexCount, meshOffset);
		else
			rendererObjectsDynamic.emplace_back(meshBaseObjectPtr, meshMaterial, meshVertexCount, meshOffset);

		if (!object->isStatic() && !dynamicIndices.empty()) {
			glBindVertexArray(dynamicVertexArrayID);
			vertexBufferDynamic->bind();
			indexBufferDynamic->bind();
			vertexBufferDynamic->setVertexLayout(Vertex::getLayout());

			vertexBufferDynamic->setData((uint32_t)dynamicVertices.size() * Vertex::getLayout().size(), &dynamicVertices[0], GL_DYNAMIC_DRAW);
			indexBufferDynamic->setData((uint32_t)dynamicIndices.size() * 4, &dynamicIndices[0], GL_DYNAMIC_DRAW);
		}
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
		
		if (!staticIndices.empty()) {
			glBindVertexArray(staticVertexArrayID);
			vertexBufferStatic->bind();
			indexBufferStatic->bind();
			vertexBufferStatic->setVertexLayout(Vertex::getLayout());

			vertexBufferStatic->setData((uint32_t)staticVertices.size() * Vertex::getLayout().size(), &staticVertices[0], GL_STATIC_DRAW);
			indexBufferStatic->setData((uint32_t)staticIndices.size() * 4, &staticIndices[0], GL_STATIC_DRAW);

			staticVertices.clear();
			staticIndices.clear();
		}

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO!!! Fix When you figure out what to do with VAO's
		glBindVertexArray(staticVertexArrayID);
		
		for (GLMesh& mesh : rendererObjectsStatic) {
			if (!mesh.object->isVisible()) 
				continue;

			mesh.material.bind(viewMatrix, projectionMatrix);
			//Renderer::getResource(mesh.getMaterialHandle())->bind();

			glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, (const void*) (mesh.offset * sizeof(uint32_t)));
		}

		//TODO!!! Fix When you figure out what to do with VAO's
		glBindVertexArray(dynamicVertexArrayID);

		for (GLMesh& mesh : rendererObjectsDynamic) {
			if (!mesh.object->isVisible())
				continue;

			mesh.material.bind(viewMatrix, projectionMatrix);
			//Renderer::getResource(mesh.materialHandle)->bind();

			glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, (const void*)(mesh.offset * sizeof(uint32_t)));
		}

		swapBuffers(window);

	}

    
	/*
      GLRenderer::~GLRenderer() {
          //TODO!!!

      }
      */
}
