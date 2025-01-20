#include "GLRenderer.h"

#ifdef STRIKE_DEBUG
#include "../Debugging/Log.h"
#endif

namespace Strike {

	GLRenderer::GLRenderer(GLFWwindow** window) {
		int glfwInitResult = glfwInit();

#ifdef STRIKE_DEBUG
		if (!glfwInitResult) Log::logError("glfw Failed to initialise!");
#endif

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		*window = glfwCreateWindow(1280, 800, "Hello World", NULL, NULL);

#ifdef STRIKE_DEBUG
		if (!window) {
			Log::logError("failed to initialise glfw window!");
			glfwTerminate();
		}
#endif

		/* Make the window's context current */
		glfwMakeContextCurrent(*window);

		int gladLoadResult = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
#ifdef STRIKE_DEBUG
		if (!gladLoadResult) Log::logError("Failed to initialize GLAD!");
#endif

		vb.init();
		ib.init();
		program.init();
	}

	bool GLRenderer::loadScene(Scene* scene) {
		//TODO!!! Test
		this->scene = scene;

		program.compileShaderFile(GL_VERTEX_SHADER, scene->getRenderableComponent().vertexSourceFilePath.c_str());
		program.compileShaderFile(GL_FRAGMENT_SHADER, scene->getRenderableComponent().fragSourceFilePath.c_str());
		program.linkProgram();
		program.useProgram();

		RenderableComponent& renderableComponent = scene->getRenderableComponent();
		renderableComponent.configureBuffers(vb, ib);

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::unordered_map<std::string, GLuint> texturePathMap;
		for (RenderableObject& object : renderableComponent.objects) {
			
			//data for creating GLObject
			int32_t vertexCountForGLObject = object.triangles.size() * 10;
			int32_t offsetInBufferForGLObject = indices.size();
			uint32_t textureIdForGLObject;

			//textures
			if (texturePathMap.find(object.texture->filePath) == texturePathMap.end()) {
				GLP::Texture texture(object.texture->filePath.c_str(), object.texture->mipmap);

				textureMap[texture.getId()] = texture;

				texturePathMap[object.texture->filePath] = texture.getId();
				textureIdForGLObject = texture.getId();
			}
			textureIdForGLObject = texturePathMap[object.texture->filePath];

			//iniitalising vertex and index buffers
			for (Triangle& triangle : object.triangles) for (Vertex& vertex : triangle.vertices) {
				int16_t index = -1;
				for (int16_t i = 0; i < vertices.size(); i++) if (vertices[i] == vertex) {
					index = i;
					break;
				}

				if (index < 0) {
					vertices.push_back(vertex);
					index = vertices.size() - 1;
				}

				indices.push_back(index);
			}

			rendererObjects.emplace_back(&object, vertexCountForGLObject, offsetInBufferForGLObject, textureIdForGLObject);
		}
		
		if(!vertices.empty()) vb.setData<float>((float*) &vertices[0], Vertex::count() * vertices.size(), GL_STATIC_DRAW);
		if(!indices.empty()) ib.setData<uint32_t>(&indices[0], indices.size(), GL_STATIC_DRAW);

		return true;
	}

	void GLRenderer::drawScene(GLFWwindow* window) {
		//TODO!!! Test
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for (GLObject& object : rendererObjects) if (object.object->visibility) {
			textureMap[object.textureID].bind();
			glDrawElements(GL_TRIANGLES, object.vertexCount, GL_UNSIGNED_INT, (const void*) object.offset);
		}

		glfwSwapBuffers(window);
	}

}