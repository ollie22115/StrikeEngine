#include "StrikePCH.h"
#include "GLTexture.h"

#include "Debugging/Log.h"

namespace Strike {

	GLTexture2D::GLTexture2D(const char* filePath, int32_t bitsPerPixel, 
		GLenum sParam, GLenum tParam, 
		GLenum minFilterParam, GLenum magFilterParam) {

		int32_t width, height;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath, &width, &height, &bitsPerPixel, bitsPerPixel);
		this->width = width;
		this->height = height;
		this->bitsPerPixel = bitsPerPixel;

#ifdef STRIKE_DEBUG
		if (!data) Log::logError(LOG_PLATFORM_OPENGL, "stbi Failed to load image");
#endif

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterParam);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}

	void GLTexture2D::bind(const uint32_t& slot) const {
		glBindTextureUnit(slot, id);
	}

	GLTexture2D::~GLTexture2D() {
		glDeleteTextures(1, &id);
	}

}