#include "Texture.h"
#include <stb.h>

Texture::Texture(const char* src, bool mipmap, int32_t bitsPerPixel, 
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, magFilterParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minFilterParam);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	if (mipmap) glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::bind(unsigned int slot){
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

Texture::~Texture(){
	glDeleteTextures(1, &id);
}
