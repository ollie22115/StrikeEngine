#pragma once

#include "EventsAndInput/EventState.h"

/*STRIKE_GLFW = glfw, STRIKE_WINDOWS = windows*/
#define STRIKE_GLFW		//TODO!!! DELETE LATER AND FIND A BETTER WAY TO CONFIGURE WINDOW PLATFORMS

namespace Strike {

	class Window {
	public:
		enum class Platform {
			None = 0, Windows, GLFW
		};

		Window(const uint32_t& width, const uint32_t& height) : width(width), height(height) {};

		inline static Platform getPlatform() { return platform; }

		inline int32_t getWidth() { return width; }
		inline int32_t getWidth() const { return width; }

		inline int32_t getHeight() { return height; }
		inline int32_t getHeight() const { return height; }

		inline const EventState& getEventState() { return eventState; }
		inline const EventState& getEventState() const { return eventState; }

		static Window* init(const uint32_t& width, const uint32_t& height, const char* title);

		virtual void onUpdate() = 0;

		virtual void setVSync(bool vSync) = 0;

		virtual ~Window() {};

	protected:
#if defined(STRIKE_GLFW)
		const static Platform platform = Platform::GLFW;
#elif defined(STRIKE_WINDOWS)
		const static Platform platform = Platform::Windows;
#else
		const static Platform platform = Platform::None;
#endif

		uint32_t width, height;

		static EventState eventState;		//Static Might cause issues
	};

}