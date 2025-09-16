#include "StrikePCH.h"
#include "GLFWWindow.h"

#include "Debugging/StrikeDebug.h"
#include "EventsAndInput/KeyButtonCode.h"
#include "EventsAndInput/MouseButtonCode.h"
#include <iostream>

namespace Strike {

	GLFWWindow::GLFWWindow(const uint32_t& maxWidth, const uint32_t& height, const char* title) :
		Window(maxWidth, height), windowHandle(nullptr) {

		int32_t result = glfwInit();
		STRIKE_ASSERT(result, LOG_PLATFORM_GLFW, "GLFW failed to initalise!");

		windowHandle = glfwCreateWindow(maxWidth, height, title, NULL, NULL);

		int actualWidth, actualHeight;
		glfwGetWindowSize(windowHandle, &actualWidth, &actualHeight);
		this->width = actualWidth;
		this->height = actualHeight;

#ifdef STRIKE_DEBUG
		if (!windowHandle) {
			Log::logError(LOG_PLATFORM_GLFW, "Window failed to initialize!");
			glfwTerminate();
		}
#endif

		glfwSetKeyCallback(windowHandle, handleKeyInput);
		glfwSetCursorPosCallback(windowHandle, handleMousePos);
		glfwSetMouseButtonCallback(windowHandle, handleMouseButtonInput);
	}

	void GLFWWindow::onUpdate() {
		eventState.windowClosed = glfwWindowShouldClose(windowHandle);

		for (uint32_t key_strike = 1; key_strike < STRIKE_TOTAL_KEYS; key_strike++) {
			if (eventState.keysPressed[key_strike]) {
				eventState.keysPressed.reset(key_strike);
				eventState.keysHeld.set(key_strike);
				eventState.keysReleased.reset(key_strike);

			}
			else if (eventState.keysReleased[key_strike]) {
				eventState.keysPressed.reset(key_strike);
				eventState.keysHeld.reset(key_strike);
				eventState.keysReleased.reset(key_strike);

			}
		}

		for (uint32_t mouseButton_strike = 1; mouseButton_strike < STRIKE_TOTAL_MOUSE_BUTTONS; mouseButton_strike++) {

			if (eventState.mouseState.buttonsPressed[mouseButton_strike]) {
				eventState.mouseState.buttonsPressed.reset(mouseButton_strike);
				eventState.mouseState.buttonsHeld.set(mouseButton_strike);
				eventState.mouseState.buttonsReleased.reset(mouseButton_strike);
			
			} else if (eventState.mouseState.buttonsReleased[mouseButton_strike]) {

				eventState.mouseState.buttonsPressed.reset(mouseButton_strike);
				eventState.mouseState.buttonsHeld.reset(mouseButton_strike);
				eventState.mouseState.buttonsReleased.reset(mouseButton_strike);
			}

		}
		

		glfwPollEvents();
	}

	void GLFWWindow::setVSync(bool vSync) {
		if (vSync) glfwSwapInterval(1);
		else glfwSwapInterval(0);
	}

    void GLFWWindow::swapBuffers() {
		glfwSwapBuffers(windowHandle);
    }

    GLFWWindow::~GLFWWindow() {
		glfwTerminate();
	}

	void GLFWWindow::handleKeyInput(GLFWwindow* window, int key_glfw, int scancode, int action, int mods) {
		
		uint32_t key_strike = keyCodeGLFWToStrike(key_glfw);
		if (key_strike == STRIKE_KEY_NONE) {
#ifdef STRIKE_DEBUG
			STRIKE_WARNING(false, LOG_PLATFORM_GLFW, "keycode not supported ");
			std::cout << key_glfw << "\n";
#endif
			return;
		}

		if (action == GLFW_PRESS) 
			eventState.registerKeyPress(key_strike);
		else if (action == GLFW_RELEASE) 
			eventState.registerKeyReleased(key_strike);
		
	}

	void GLFWWindow::handleMouseButtonInput(GLFWwindow*, int mouseButton_glfw, int action, int mods) {
		uint32_t mouseButton_strike = mouseButtonCodeGLFWToStrike(mouseButton_glfw);

		if (action == GLFW_PRESS)
			eventState.registerMouseButtonPressed(mouseButton_strike);
		else if (action == GLFW_RELEASE)
			eventState.registerMouseButtonReleased(mouseButton_strike);
		
	}

	void GLFWWindow::handleMousePos(GLFWwindow* window, double xPos, double yPos) {
		eventState.setMousePosition(xPos, yPos);
	}

	uint32_t GLFWWindow::keyCodeGLFWToStrike(const uint32_t& key_strike) {
		switch (key_strike) {
			case GLFW_KEY_LEFT: return STRIKE_KEY_LEFT;
			case GLFW_KEY_RIGHT: return STRIKE_KEY_RIGHT;
			case GLFW_KEY_UP: return STRIKE_KEY_UP;
			case GLFW_KEY_DOWN: return STRIKE_KEY_DOWN;

			case GLFW_KEY_SPACE: return STRIKE_KEY_SPACE;

			case GLFW_KEY_0: return STRIKE_KEY_0;
			case GLFW_KEY_1: return STRIKE_KEY_1;
			case GLFW_KEY_2: return STRIKE_KEY_2;
			case GLFW_KEY_3: return STRIKE_KEY_3;
			case GLFW_KEY_4: return STRIKE_KEY_4;
			case GLFW_KEY_5: return STRIKE_KEY_5;
			case GLFW_KEY_6: return STRIKE_KEY_6;
			case GLFW_KEY_7: return STRIKE_KEY_7;
			case GLFW_KEY_8: return STRIKE_KEY_8;
			case GLFW_KEY_9: return STRIKE_KEY_9;

			case GLFW_KEY_COMMA: return STRIKE_KEY_COMMA;

			case GLFW_KEY_ESCAPE: return STRIKE_KEY_ESCAPE;
			case GLFW_KEY_F1: return STRIKE_KEY_F1;
			case GLFW_KEY_F2: return STRIKE_KEY_F2;
			case GLFW_KEY_F3: return STRIKE_KEY_F3;
			case GLFW_KEY_F4: return STRIKE_KEY_F4;
			case GLFW_KEY_F5: return STRIKE_KEY_F5;
			case GLFW_KEY_F6: return STRIKE_KEY_F6;
			case GLFW_KEY_F7: return STRIKE_KEY_F7;
			case GLFW_KEY_F8: return STRIKE_KEY_F8;
			case GLFW_KEY_F9: return STRIKE_KEY_F9;
			case GLFW_KEY_F10: return STRIKE_KEY_F10;
			case GLFW_KEY_F11: return STRIKE_KEY_F11;
			case GLFW_KEY_F12: return STRIKE_KEY_F12;
			case GLFW_KEY_INSERT: return STRIKE_KEY_INSERT;
			case GLFW_KEY_DELETE: return STRIKE_KEY_DELETE;
			case GLFW_KEY_TAB: return STRIKE_KEY_TAB;
			case GLFW_KEY_LEFT_SHIFT: return STRIKE_KEY_LEFT_SHIFT;
			case GLFW_KEY_RIGHT_SHIFT: return STRIKE_KEY_RIGHT_SHIFT;
			case GLFW_KEY_CAPS_LOCK: return STRIKE_KEY_CAPS_LOCK;
			case GLFW_KEY_LEFT_CONTROL: return STRIKE_KEY_LEFT_CONTROL;
			case GLFW_KEY_RIGHT_CONTROL: return STRIKE_KEY_RIGHT_CONTROL;
			case GLFW_KEY_LEFT_ALT: return STRIKE_KEY_LEFT_ALT;
			case GLFW_KEY_RIGHT_ALT: return STRIKE_KEY_RIGHT_ALT;
			case GLFW_KEY_LEFT_BRACKET: return STRIKE_KEY_LBRACKET;
			case GLFW_KEY_RIGHT_BRACKET: return STRIKE_KEY_RBRAKCET;
			case GLFW_KEY_BACKSPACE: return STRIKE_KEY_BACKSPACE;
			case GLFW_KEY_SEMICOLON: return STRIKE_KEY_SEMICOLON;
			case GLFW_KEY_SLASH: return STRIKE_KEY_SLASH;
			case GLFW_KEY_PERIOD: return STRIKE_KEY_FULLSTOP;
			case GLFW_KEY_APOSTROPHE: return STRIKE_KEY_APOSTROPHE;
			case GLFW_KEY_ENTER: return STRIKE_KEY_ENTER;

			case GLFW_KEY_A: return STRIKE_KEY_A;
			case GLFW_KEY_B: return STRIKE_KEY_B;
			case GLFW_KEY_C: return STRIKE_KEY_C;
			case GLFW_KEY_D: return STRIKE_KEY_D;
			case GLFW_KEY_E: return STRIKE_KEY_E;
			case GLFW_KEY_F: return STRIKE_KEY_F;
			case GLFW_KEY_G: return STRIKE_KEY_G;
			case GLFW_KEY_H: return STRIKE_KEY_H;
			case GLFW_KEY_I: return STRIKE_KEY_I;
			case GLFW_KEY_J: return STRIKE_KEY_J;
			case GLFW_KEY_K: return STRIKE_KEY_K;
			case GLFW_KEY_L: return STRIKE_KEY_L;
			case GLFW_KEY_M: return STRIKE_KEY_M;
			case GLFW_KEY_N: return STRIKE_KEY_N;
			case GLFW_KEY_O: return STRIKE_KEY_O;
			case GLFW_KEY_P: return STRIKE_KEY_P;
			case GLFW_KEY_Q: return STRIKE_KEY_Q;
			case GLFW_KEY_R: return STRIKE_KEY_R;
			case GLFW_KEY_S: return STRIKE_KEY_S;
			case GLFW_KEY_T: return STRIKE_KEY_T;
			case GLFW_KEY_U: return STRIKE_KEY_U;
			case GLFW_KEY_V: return STRIKE_KEY_V;
			case GLFW_KEY_W: return STRIKE_KEY_W;
			case GLFW_KEY_X: return STRIKE_KEY_X;
			case GLFW_KEY_Y: return STRIKE_KEY_Y;
			case GLFW_KEY_Z: return STRIKE_KEY_Z;
		}

		//Key Not Supported
		return STRIKE_KEY_NONE;
	}

	uint32_t GLFWWindow::mouseButtonCodeGLFWToStrike(const uint32_t& mouseButton_glfw) {

		switch(mouseButton_glfw) {
			case(GLFW_MOUSE_BUTTON_LEFT): return STRIKE_MOUSE_BUTTON_LEFT;
			case(GLFW_MOUSE_BUTTON_RIGHT): return STRIKE_MOUSE_BUTTON_RIGHT;
			case(GLFW_MOUSE_BUTTON_MIDDLE): return STRIKE_MOUSE_BUTTON_MIDDLE;
		}
		
		return STRIKE_MOUSE_BUTTON_NONE;
	}

}