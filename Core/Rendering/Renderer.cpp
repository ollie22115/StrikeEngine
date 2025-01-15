#include "Renderer.h"

#ifdef STRIKE_DEBUG
#include "../Debugging/Log.h"
#endif

SceneRenderer::SceneRenderer(GLFWwindow** window) {
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

bool SceneRenderer::loadScene(const Scene* scene) {
    //TODO!!!
	program.compileShaderFile(GL_VERTEX_SHADER, scene->getVertexSourceFilePath().c_str());
	program.compileShaderFile(GL_FRAGMENT_SHADER, scene->getFragSourceFilePath().c_str());
	program.linkProgram();
	program.useProgram();

    return false;
}

void SceneRenderer::drawScene(GLFWwindow* window) {
    //TODO!!!
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
}
