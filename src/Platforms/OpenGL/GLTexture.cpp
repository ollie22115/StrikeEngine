#include "StrikePCH.h"
#include "GLTexture.h"

#include "Debugging/Log.h"
#include "Utils/FileLoader.h"


namespace Strike {

	GLTexture2D::GLTexture2D(int32_t bitsPerPixel, GLenum sParam, GLenum tParam, GLenum minFilterParam, GLenum magFilterParam) {
		this->width = 1;
		this->height = 1;
		this->bitsPerPixel = bitsPerPixel;

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterParam);

		GLubyte data[4] = { 255, 255, 255, 255 };

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);
	}

    GLTexture2D::GLTexture2D(unsigned char* data, int32_t width, int32_t height, 
		int32_t bitsPerPixel, GLenum sParam, GLenum tParam, GLenum minFilterParam, GLenum magFilterParam) {
		//TODO!!! TEST
		this->width = width;
		this->height = height;
		this->bitsPerPixel = bitsPerPixel;

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterParam);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    GLTexture2D::GLTexture2D(const char* filePath, int32_t bitsPerPixel,
		GLenum sParam, GLenum tParam, 
		GLenum minFilterParam, GLenum magFilterParam) {
			
		//TODO!!! Delete once ResourceManager is up and running
		int32_t width, height;
	
		auto textureData = FileLoader::genTextureFromImage(filePath, bitsPerPixel);

		this->width = textureData.width;
		this->height = textureData.height;
		this->bitsPerPixel = textureData.bitsPerPixel;

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterParam);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, 
			GL_RGBA, GL_UNSIGNED_BYTE, textureData.data);

	}

    GLTexture2D::GLTexture2D(const TextureData2D &textureData) {
		//TODO!!! TEST
		GLenum sParam = GL_REPEAT;
		GLenum tParam = GL_REPEAT; 
		GLenum minFilterParam = GL_LINEAR;
		GLenum magFilterParam = GL_LINEAR;

		this->width = textureData.width;
		this->height = textureData.height;
		this->bitsPerPixel = textureData.bitsPerPixel;

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterParam);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, textureData.data);
    }

    GLTexture2D::GLTexture2D(const GLTexture2D& other) {
		this->id = other.getId();
		this->width = other.getWidth();
		this->height = other.getHeight();
		this->bitsPerPixel = other.getBitsPerPixel();
    }

    void GLTexture2D::bind(const uint32_t& slot) const {
		glBindTextureUnit(slot, id);
	}

	GLTexture2D::~GLTexture2D() {
		glDeleteTextures(1, &id);
	}

}