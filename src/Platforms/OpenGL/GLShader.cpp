#include "StrikePCH.h"
#include "GLShader.h"

#ifdef STRIKE_DEBUG
#include "Debugging/Log.h"
#endif

namespace Strike {

	GLVertexShader::GLVertexShader(const char* src) {
		id = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(id, 1, &src, NULL);
		glCompileShader(id);

#ifdef STRIKE_DEBUG
		GLint compilationResult;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);

		if (!compilationResult) {
			char infoLog[512];

			glGetShaderInfoLog(id, 512, NULL, infoLog);
			Log::logError(LOG_PLATFORM_OPENGL, { "Shader Failed to Load ", infoLog });
		}
#endif

	}

	GLVertexShader::~GLVertexShader() {
		glDeleteShader(id);
	}



	GLPixelShader::GLPixelShader(const char* src) {
		id = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(id, 1, &src, NULL);
		glCompileShader(id);

#ifdef STRIKE_DEBUG
		GLint compilationResult;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compilationResult);

		char infoLog[512];
		if (!compilationResult) {
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			Log::logError(LOG_PLATFORM_OPENGL, { "Shader Failed to Load ", infoLog });
		}
#endif
	}

	GLPixelShader::~GLPixelShader() {
		glDeleteShader(id);
	}

}