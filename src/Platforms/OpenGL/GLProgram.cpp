#include "StrikePCH.h"
#include "GLProgram.h"

#include "Debugging/StrikeDebug.h"
#include "Debugging/Log.h"


#include <iostream>//TODO!!! DELETE LATER

namespace Strike {

	GLProgram::GLProgram() {
		id = glCreateProgram();
	}

    GLProgram::GLProgram(const ShaderData &shaderData) {
		id = glCreateProgram();
		compile(shaderData.vertexSrc, shaderData.fragSrc);
    }

    void GLProgram::compile(const std::string &vertexSrc, const std::string &fragmentSrc) {
		GLVertexShader vertexShader(vertexSrc.c_str());
		GLPixelShader pixelShader(fragmentSrc.c_str());

		glAttachShader(id, vertexShader.getId());
		glAttachShader(id, pixelShader.getId());

		glLinkProgram(id);
    }

    void GLProgram::bind() const {
		glUseProgram(id);
	}

	void GLProgram::setUniform4f(const std::string& uniformName, float f1, float f2, float f3, float f4) {
		
		if (uniforms.find(uniformName) == uniforms.end()) {
			int uniformLocation = glGetUniformLocation(id, uniformName.c_str());

#ifdef STRIKE_DEBUG
			if (uniformLocation < 0) 
				Log::logError(LOG_PLATFORM_OPENGL, "Failed to initialise uniform!");
#endif

			uniforms[uniformName] = uniformLocation;
		}

		glUniform4f(uniforms[uniformName], f1, f2, f3, f4);
	}

	void GLProgram::setUniformMat4f(const std::string& uniformName, const glm::mat4& matrix, GLenum transpose) {
		if (uniforms.find(uniformName) == uniforms.end()) {
			int uniformLocation = glGetUniformLocation(id, uniformName.c_str());
			
			STRIKE_ASSERT(uniformLocation >= 0, LOG_PLATFORM_OPENGL, "Failed to initialised uniform!");

			uniforms[uniformName] = uniformLocation;
		}

		glUniformMatrix4fv(uniforms[uniformName], 1, transpose, &matrix[0][0]);
	}

	GLProgram::~GLProgram() {
		glDeleteProgram(id);
	}

}