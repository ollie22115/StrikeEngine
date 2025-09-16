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

		inline void registerKeyPress(const uint32_t& keyCode) {
			keysPressed.set(keyCode);
			keysHeld.set(keyCode);
			keysReleased.reset(keyCode);
		}

		inline void registerKeyReleased(const uint32_t& keyCode) {
			keysPressed.reset(keyCode);
			keysHeld.reset(keyCode);
			keysReleased.set(keyCode);
		}

		inline void registerMouseButtonPressed(const uint32_t& mouseButtonCode) {
			mouseState.buttonsPressed.set(mouseButtonCode);
			mouseState.buttonsHeld.set(mouseButtonCode);
			mouseState.buttonsReleased.reset(mouseButtonCode);
		}

		inline void registerMouseButtonReleased(const uint32_t& mouseButtonCode) {
			mouseState.buttonsPressed.reset(mouseButtonCode);
			mouseState.buttonsHeld.reset(mouseButtonCode);
			mouseState.buttonsReleased.set(mouseButtonCode);
		}

		inline void setMousePosition(const uint32_t& xPos, const uint32_t& yPos) {
			mouseState.xPos = xPos;
			mouseState.yPos = yPos;
		}


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