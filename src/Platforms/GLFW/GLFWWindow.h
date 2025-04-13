#pragma once

#include "Window.h"
#include <GLFW/glfw3.h>

namespace Strike {

	class GLFWWindow : public Window {
	public:
		GLFWWindow(const uint32_t& width, const uint32_t& height, const char* title = "GLFWWindow!");

		inline GLFWwindow* getGLFWWindowHandle() const { return windowHandle; }

		void onUpdate() override;

		void setVSync(bool vSync) override;

		~GLFWWindow() override;

	private:
		GLFWwindow* windowHandle;

		static uint32_t keyCodeGLFWToStrike(const uint32_t& key_glfw);
		static uint32_t mouseButtonCodeGLFWToStrike(const uint32_t& mouseButton_glfw);

		static void handleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void handleMouseButtonInput(GLFWwindow*, int mouseButton_glfw, int action, int mods);
		static void handleMousePos(GLFWwindow* window, double xPos, double yPos);
	};

}