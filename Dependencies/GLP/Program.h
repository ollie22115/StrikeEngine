#pragma once
#include <glad/glad.h>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

#ifdef GLP_DEBUG
#include <iostream>
#endif

namespace GLP {

	class Shader {
	public:
		Shader(const GLenum target);

		inline GLuint getID() { return id; };
		inline GLuint getID() const { return id; };

		inline GLenum getType() { return type; }
		inline GLenum getType() const { return type; }

		int compileShader(const char* src);

		~Shader();

	private:
		const GLenum type;
		GLuint id;
	};

	class Program {
	public:
		Program() = default;

		void init();

		inline GLuint getID() { return id; }
		inline GLuint getID() const { return id; }

		void compileShaderFile(GLenum type, const char* path);
		void compileShader(GLenum type, const char* src);
		GLint linkProgram();
		void useProgram();

		bool setUniform4f(const char* uniformName, float f1, float f2, float f3, float f4);
		bool setUniformMat4f(const char* uniformName, const glm::mat4& matrix, GLenum transpose);

		~Program();

	private:
		GLuint id;
		::std::vector<Shader> shaders;
		::std::unordered_map<const char*, GLint> uniforms;
	};

}