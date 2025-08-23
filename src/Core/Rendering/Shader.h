#pragma once

#define STRIKE_SHADER_VERTEX		1
#define STRIKE_SHADER_PIXEL			2

#ifdef STRIKE_OPENGL
#include "OpenGL/GLProgram.h"
#endif

namespace Strike {

#ifdef STRIKE_OPENGL
	using Shader = GLProgram;
#endif

	//TODO!!! POSSIBLY USELESS CODE
	class ShaderCore {
	public:
		ShaderCore(const std::string& filePath) : filePath(filePath) {};
		inline const std::string& getFilePath() const { return filePath; }

		bool operator ==(const ShaderCore& other) const;

	private:
		std::string filePath;
	};
	//USELESS CODE END!!!

}