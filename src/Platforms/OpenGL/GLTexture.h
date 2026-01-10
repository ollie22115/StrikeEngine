#pragma once

#include <glad/glad.h>
#include "Resource/ResourceData.h"

namespace Strike {

	class GLTexture2D{
	public:

		GLTexture2D(int32_t bitsPerPixel = 4, int32_t width = 1, int32_t height = 1,
			GLenum sParam = GL_REPEAT, GLenum tParam = GL_REPEAT,
			GLenum minFilterParam = GL_LINEAR, GLenum magFilterParam = GL_LINEAR);

		GLTexture2D(unsigned char* data, int32_t width, int32_t height, int32_t bitsPerPixel = 4, GLenum sParam = GL_REPEAT, 
			GLenum tParam = GL_REPEAT, GLenum minFilterParam = GL_LINEAR, GLenum magFilterParam = GL_LINEAR);

		GLTexture2D(const TextureData2D& textureData);

		GLTexture2D(const GLTexture2D& other);


		inline GLuint getId() { return id; }
		inline GLuint getId() const { return id; }

		inline int32_t getWidth() { return width; }
		inline int32_t getWidth() const { return width; }

		inline int32_t getHeight() { return height; }
		inline int32_t getHeight() const { return height; }

		inline int32_t getBitsPerPixel() { return bitsPerPixel; }
		inline int32_t getBitsPerPixel() const { return bitsPerPixel; }

		inline bool operator==(const GLTexture2D& other) const { return id == other.id; }

		void bind(const uint32_t& slot = 0) const;

		~GLTexture2D();

	private:
		GLuint id;
		uint32_t width, height, bitsPerPixel;
	};

}