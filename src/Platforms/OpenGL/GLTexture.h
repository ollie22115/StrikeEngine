#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include "Rendering/Texture.h"

namespace Strike {

	class GLTexture2D{
	public:

		GLTexture2D(int32_t bitsPerPixel = 4, 
			GLenum sParam = GL_REPEAT, GLenum tParam = GL_REPEAT,
			GLenum minFilterParam = GL_LINEAR, GLenum magFilterParam = GL_LINEAR);

		GLTexture2D(const char* filePath, int32_t bitsPerPixel = 4,
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

		void bind(const uint32_t& slot = 0) const;

		~GLTexture2D();

	private:
		GLuint id;
		uint32_t width, height, bitsPerPixel;
	};

}