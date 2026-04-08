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

    

	void GLRenderer::loadStaticRenderable(const Renderable& renderable) {
		const std::vector<Vertex>& objectVertices = renderable.getVertices();

		size_t meshVertexCount = objectVertices.size();
		size_t meshOffset = staticIndices.size();
		ResourcePointer<Material> meshMaterial = renderable.materialPtr;

		for (const Vertex& objectVertex : objectVertices) {
			int32_t index = -1;

			for (int i = 0; i < staticVertices.size(); i++) 
				if (staticVertices[i] == objectVertex) {
					index = i;
					break;
			}

			if (index < 0) {
				staticVertices.push_back(objectVertex);
				index = (int32_t)staticVertices.size() - 1;
			}

			staticIndices.push_back(index);
		}

		rendererObjectsStatic.emplace_back(meshMaterial, meshVertexCount, meshOffset);
	}

	void GLRenderer::drawDynamicRenderable(const Renderable& renderable) {
		const std::vector<Vertex>& objectVertices = renderable.getVertices();

		size_t meshVertexCount = objectVertices.size();
		size_t meshOffset = dynamicIndices.size();
		ResourcePointer<Material> meshMaterial = renderable.materialPtr;

		for (const Vertex& objectVertex : objectVertices) {
			int32_t index = -1;

			for (int i = 0; i < dynamicVertices.size(); i++) 
				if (dynamicVertices[i] == objectVertex) {
					index = i;
					break;
			}

			if (index < 0) {
				dynamicVertices.push_back(objectVertex);
				index = (int32_t)dynamicVertices.size() - 1;
			}

			dynamicIndices.push_back(index);
		}
			
		rendererObjectsDynamic.emplace_back(meshMaterial, meshVertexCount, meshOffset);
	}

	void GLRenderer::flush(std::shared_ptr<Window>& window, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
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

		if (!dynamicIndices.empty()) {
			glBindVertexArray(dynamicVertexArrayID);
			vertexBufferDynamic->bind();
			indexBufferDynamic->bind();
			vertexBufferDynamic->setVertexLayout(Vertex::getLayout());

			vertexBufferDynamic->setData((uint32_t)dynamicVertices.size() * Vertex::getLayout().size(), &dynamicVertices[0], GL_DYNAMIC_DRAW);
			indexBufferDynamic->setData((uint32_t)dynamicIndices.size() * 4, &dynamicIndices[0], GL_DYNAMIC_DRAW);

			dynamicVertices.clear();
			dynamicIndices.clear();
		}

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		//TODO!!! Fix When you figure out what to do with VAO's
		glBindVertexArray(staticVertexArrayID);
		
		for (GLMesh& mesh : rendererObjectsStatic) {
			mesh.materialPtr->bind(viewMatrix, projectionMatrix);

			glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, (const void*) (mesh.offset * sizeof(uint32_t)));
		}

		//TODO!!! Fix When you figure out what to do with VAO's
		glBindVertexArray(dynamicVertexArrayID);

		for (GLMesh& mesh : rendererObjectsDynamic) {
			mesh.materialPtr->bind(viewMatrix, projectionMatrix);

			glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, (const void*)(mesh.offset * sizeof(uint32_t)));
		}

		swapBuffers(window);

		rendererObjectsDynamic.clear();
	}

    GLRenderer::~GLRenderer() {
		//TODO!!! 
    }

    /*
      GLRenderer::~GLRenderer() {
          //TODO!!!

      }
    */
}
