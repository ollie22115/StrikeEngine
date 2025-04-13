#include "StrikePCH.h"

#define STRIKE_GLFW		//TODO!!! BAD CODE DELETE LATER!!!

#if defined(STRIKE_GLFW)
#include "../Platforms/GLFW/GLFWWindow.h"
#else if defined(STRIKE_WINDOWS)
#include "../Platforms/Windows/WindowsWindow.h"
#endif

#include "Debugging/StrikeDebug.h"

namespace Strike {

	EventState Window::eventState;		//static member declared in this way could be very dodgy

	Window* Window::init(const uint32_t& width, const uint32_t& height, const char* title) {
		switch (platform) {
			case Platform::GLFW:
				return new GLFWWindow(width, height, title);
			case Platform::Windows:
				STRIKE_ASSERT(false, LOG_PLATFORM_CORE, "Windows not supported yet");
		}
	}

}
