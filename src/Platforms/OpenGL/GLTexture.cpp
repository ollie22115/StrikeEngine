#include "StrikePCH.h"
#include "GLTexture.h"

#include "Debugging/Log.h"
#include "Utils/FileLoader.h"


namespace Strike {

	GLTexture2D::GLTexture2D(int32_t bitsPerPixel, int32_t width, int32_t height, GLenum sParam, GLenum tParam, GLenum minFilterParam, GLenum magFilterParam) {
		this->width = width;
		this->height = height;
		this->bitsPerPixel = bitsPerPixel;

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterParam);

		std::unique_ptr<GLubyte[]> data = std::make_unique<GLubyte[]>(bitsPerPixel * width * height);
		for(int i = 0; i < width * height * bitsPerPixel; i++)
			data[i] = 255;

		GLenum glInternalFormat = bitsPerPixelToGLInternalFormatEnum(bitsPerPixel);
		GLenum glCPUFormat = bitsPerPixelToCPUFormatEnum(bitsPerPixel);

		glTexImage2D(GL_TEXTURE_2D, 0, glInternalFormat, width, height, 0, glCPUFormat, GL_UNSIGNED_BYTE, data.get());
	}

    GLTexture2D::GLTexture2D(unsigned char* data, int32_t width, int32_t height, 
		int32_t bitsPerPixel, int32_t internalBitsPerPixel, GLenum sParam, GLenum tParam, GLenum minFilterParam, GLenum magFilterParam) {
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

		GLenum glInternalFormat = bitsPerPixelToGLInternalFormatEnum(internalBitsPerPixel);
		GLenum glCPUFormat = bitsPerPixelToCPUFormatEnum(bitsPerPixel);

		glTexImage2D(GL_TEXTURE_2D, 0, glInternalFormat, width, height, 0,
			glCPUFormat, GL_UNSIGNED_BYTE, data);
    }

    GLTexture2D::GLTexture2D(const TextureData2D &textureData) {
		GLenum sParam = GL_REPEAT;
		GLenum tParam = GL_REPEAT; 
		GLenum minFilterParam = GL_LINEAR;
		GLenum magFilterParam = GL_LINEAR;

		this->width = textureData.width;
		this->height = textureData.height;
		this->bitsPerPixel = textureData.desiredInternalBitsPerPixel;

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterParam);

		GLenum glInternalFormat = bitsPerPixelToGLInternalFormatEnum(bitsPerPixel);
		GLenum glCPUFormat = bitsPerPixelToCPUFormatEnum(textureData.bitsPerPixel);

		glTexImage2D(GL_TEXTURE_2D, 0, glInternalFormat, width, height, 0,
			glCPUFormat, GL_UNSIGNED_BYTE, textureData.data.get());
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

    GLenum GLTexture2D::bitsPerPixelToGLInternalFormatEnum(const uint32_t &bitsPerPixel) {
        
		switch(bitsPerPixel) {
			case 1: return GL_R8;
			case 2: return GL_RG8;
			case 3: return GL_RGB8;
			case 4: return GL_RGBA8;
			default:
				STRIKE_ASSERT(false, LOG_PLATFORM_OPENGL, "Desired Bits per pixel cannot be higher than 4 or lower than 1!");
		}

    }

    GLenum GLTexture2D::bitsPerPixelToCPUFormatEnum(const uint32_t &bitsPerPixel) {
        
		switch(bitsPerPixel) {
			case 1: return GL_RED;
			case 2: return GL_RG;
			case 3: return GL_RGB;
			case 4: return GL_RGBA;
			default:
				STRIKE_ASSERT(false, LOG_PLATFORM_OPENGL, "Bits per pixel cannot be higher than 4 or lower than 1!");
		}

    }
}