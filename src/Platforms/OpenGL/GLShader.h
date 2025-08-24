#pragma once

#include <string>
#include <glad/glad.h>

namespace Strike {

	class GLVertexShader {
	public:
		GLVertexShader(const char* src);

		inline GLuint getId() { return id; }

		~GLVertexShader();

	private:
		GLuint id;
	};

	class GLPixelShader {
	public:
		GLPixelShader(const char* src);

		inline GLuint getId() { return id; }

		~GLPixelShader();

	private:
		GLuint id;
	};

}