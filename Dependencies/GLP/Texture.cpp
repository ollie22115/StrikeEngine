#include "Texture.h"
#include <stb.h>

GLP::Texture::Texture(const char* src, int32_t bitsPerPixel, 
							GLenum sParam, GLenum tParam, 
							GLenum magFilterParam, GLenum minFilterParam) : id(0), width(0), height(0), bitsPerPixel(bitsPerPixel) {

	unsigned char* data = stbi_load(src, &width, &height, &bitsPerPixel, bitsPerPixel);

#ifdef GLP_DEBUG
	if (!data) std::cout << "stbi Failed to load image\n";
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

void GLP::Texture::bind(unsigned int slot){
	glActiveTexture(GL_TEXTURE0 + slot);

	glBindTexture(GL_TEXTURE_2D, id);
}

GLP::Texture::~Texture(){
	glDeleteTextures(1, &id);
}

GLP::Mipmap::Mipmap(const char* src, int32_t bitsPerPixel, GLenum minFilterParam, GLenum magFilterParam, GLenum sParam, GLenum tParam) : 
	Texture(src, bitsPerPixel, sParam, tParam, magFilterParam, minFilterParam) {

	glGenerateMipmap(GL_TEXTURE_2D);
}