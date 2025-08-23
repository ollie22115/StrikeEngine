#pragma once

#ifdef STRIKE_OPENGL
#include "OpenGL/GLTexture.h"
#endif

#define STRIKE_TEXTURE2D 1

namespace Strike {
#ifdef STRIKE_OPENGL
	using Texture2D = GLTexture2D;
#endif

	//POSSIBLE CODE!!! STILL NEED TO THINK THROUGH
	/*
	class Texture {
	public:
		std::string getPath();
		std::string setPath(const std::stirng& path);

		virtual int32_t getWidth() = 0;
		virtual int32_t getHeight() = 0;
		virtual Vector2 getScreenCoords() = 0;

	private:
		//This will change when texture loading changes so keep it in mind
		std::string path;
	};

	class Texture2D : Texture
	*/
	//POSSIBLE CODEEE END!!!

	//TODO!!!: THIS CLASS MAY BE USELESS REMOVE IF NOT BEING USED
	class TextureCore {
	public:
		TextureCore() = default;
		TextureCore(const std::string& filePath) : filePath(filePath) {};

		inline const std::string& getFilePath() const { return filePath; }

		bool operator ==(const TextureCore& other) const;

	private:
		std::string filePath = "Default";
	};
	//WARNING!!!: POSSIBLY USELESS CODE END

}