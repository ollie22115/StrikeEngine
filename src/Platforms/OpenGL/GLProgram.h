#pragma once

#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GLShader.h"

namespace Strike {

	class GLProgram {
	public:
		GLProgram();
		
		inline GLuint getID() { return id; }
		inline GLuint getID() const { return id; }

		void compile(const std::string& src);

		void bind();

		void setUniform4f(std::string& uniformName, float f1, float f2, float f3, float f4);
		void setUniformMat4f(std::string& uniformName, const glm::mat4& matrix, GLenum transpose);

		~GLProgram();

	private:
		GLuint id;

		std::unordered_map<std::string, GLint> uniforms;
	};

}