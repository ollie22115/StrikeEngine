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

    void GLProgram::compile(const std::string& src) {
		std::stringstream srcStream;
		srcStream << src;
		std::stringstream vertexShaderSrc;
		std::stringstream pixelShaderSrc;
		std::string line;
		uint32_t shaderType = 0;	//0 = none, 1 = vertex, 2 = pixel
		while (getline(srcStream, line)) {
			if (line.find("#type vertex") != std::string::npos)
				shaderType = 1;
			else if (line.find("#type pixel") != std::string::npos)
				shaderType = 2;
			else {
				STRIKE_ASSERT(shaderType > 0 && shaderType < 3, LOG_PLATFORM_OPENGL, "Error shader source must have a type");

				switch (shaderType) {
					case 1:
						vertexShaderSrc << line << "\n";
						break;

					case 2:
						pixelShaderSrc << line << "\n";
						break;
				}
			}
		}

		//TODO!!! take in default shaders if none were defined
		GLVertexShader vertexShader(vertexShaderSrc.str().c_str());
		GLPixelShader pixelShader(pixelShaderSrc.str().c_str());
		
		//TODO!!! may not to keep shaders around
		glAttachShader(id, vertexShader.getId());
		glAttachShader(id, pixelShader.getId());

		glLinkProgram(id);

#ifdef STRIKE_DEBUG
		GLint linkResult;
		glGetProgramiv(id, GL_LINK_STATUS, &linkResult);

		if (!linkResult) {
			char infoLog[512];
			glGetProgramInfoLog(id, 512, NULL, infoLog);

			Log::logError(LOG_PLATFORM_OPENGL, { "Program failed to link! ", infoLog });
		}
#endif
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