#pragma once

#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "GLShader.h"
#include "Resource/ResourceData.h"

namespace Strike {

	class GLProgram {
	public:
		GLProgram();
		GLProgram(const ShaderData& shaderData);
		
		inline GLuint getID() { return id; }
		inline GLuint getID() const { return id; }

		void compile(const std::string& vertexSrc, const std::string& fragmentSrc);

		void bind() const;

		void setUniform4f(const std::string& uniformName, float f1, float f2, float f3, float f4);
		void setUniformMat4f(const std::string& uniformName, const glm::mat4& matrix, GLenum transpose);

		~GLProgram();

	private:
		GLuint id;

		std::unordered_map<std::string, GLint> uniforms;
	};

}