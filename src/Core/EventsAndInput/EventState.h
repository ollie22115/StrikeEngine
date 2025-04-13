#pragma once

#include <bitset>
#include <array>

#include "Event.h"

namespace Strike {

	struct MouseState {
		std::bitset<8> buttonsPressed;
		std::bitset<8> buttonsHeld;
		std::bitset<8> buttonsReleased;

		float xPos;
		float yPos;
	};

	struct EventState {
		/*Seperate keyPressed, keysHeld and keysReleased into KeyState*/
		std::bitset<256> keysPressed;
		std::bitset<256> keysHeld;
		std::bitset<256> keysReleased;
		MouseState mouseState;

		bool windowClosed = false;
		bool windowFullScreen = false;
		bool windowMinimised = false;

		inline bool isKeyPressed(const uint64_t& keyCode) { return keysPressed[keyCode]; }
		inline bool isKeyPressed(const uint64_t& keyCode) const { return keysPressed[keyCode]; }

		inline bool isKeyHeld(const uint64_t& keyCode) { return keysHeld[keyCode]; }
		inline bool isKeyHeld(const uint64_t& keyCode) const { return keysHeld[keyCode]; }

		inline bool isKeyReleased(const uint64_t& keyCode) { return keysReleased[keyCode]; }
		inline bool isKeyReleased(const uint64_t& keyCode) const { return keysReleased[keyCode]; }

		inline bool isMouseButtonPressed(const uint8_t& mouseButtonCode) { return mouseState.buttonsPressed[mouseButtonCode]; }
		inline bool isMouseButtonPressed(const uint8_t& mouseButtonCode) const { return mouseState.buttonsPressed[mouseButtonCode]; }

		inline bool isMouseButtonHeld(const uint8_t& mouseButtonCode) { return mouseState.buttonsHeld[mouseButtonCode]; }
		inline bool isMouseButtonHeld(const uint8_t& mouseButtonCode) const { return mouseState.buttonsHeld[mouseButtonCode]; }

		inline bool isMouseButtonReleased(const uint8_t& mouseButtonCode) { return mouseState.buttonsReleased[mouseButtonCode]; }
		inline bool isMouseButtonReleased(const uint8_t& mouseButtonCode) const { return mouseState.buttonsReleased[mouseButtonCode]; }

		//0 = x, 1 = y
		inline std::array<float, 2> getMousePos() { return {mouseState.xPos, mouseState.yPos}; }

		inline bool isWindowClosed() { return windowClosed; }
	};

}