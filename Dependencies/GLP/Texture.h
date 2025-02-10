#pragma once
#include <iostream>
#include <glad/glad.h>

namespace GLP {

	//add move constructor to this class

	class Texture {
	public:
		Texture() = default;	//TODO!!! look over this class and give it a better constructor
		Texture(const char* src, int32_t bitsPerPixel = 4,
			GLenum sParam = GL_REPEAT, GLenum tParam = GL_REPEAT,
			GLenum minFilterParam = GL_LINEAR,
			GLenum magFilterParam = GL_LINEAR);

		inline GLuint getId() { return id; }
		inline GLuint getId() const { return id; }

		inline int32_t getWidth() { return width; }
		inline int32_t getWidth() const { return width; }

		inline int32_t getHeight() { return height; }
		inline int32_t getHeight() const { return height; }

		inline int32_t getBitsPerPixel() { return bitsPerPixel; }
		inline int32_t getBitsPerPixel() const { return bitsPerPixel; }

		void bind(unsigned int slot = 0);

		~Texture();

	protected:
		GLuint id;
		int32_t width, height, bitsPerPixel;
	};

	class Mipmap : public Texture {
	public:
		Mipmap() = default;	//TODO!!! look over this class and give it a better constructor
		Mipmap(const char* src, int32_t bitsPerPixel = 4,
			GLenum minFilterParam = GL_LINEAR_MIPMAP_LINEAR,
			GLenum magFilterParam = GL_LINEAR,
			GLenum sParam = GL_REPEAT, GLenum tParam = GL_REPEAT);
	};
}