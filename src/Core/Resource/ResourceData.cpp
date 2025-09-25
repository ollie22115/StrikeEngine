#include "ResourceData.h"
#include <stb_image.h>

namespace Strike{
    
    TextureData2D::TextureData2D() {
        usingSTBI = false;

        this->width = 1;
		this->height = 1;
		this->bitsPerPixel = bitsPerPixel;

		data = new unsigned char[4];  // 4 bytes per pixel

        data[0] = 255;
        data[1] = 255;
        data[2] = 255;
        data[3] = 255;
    }

    TextureData2D::TextureData2D(TextureData2D &&other) {
        this->data = other.data;
        this->width = other.width;
        this->height = other.height;
        this->bitsPerPixel = other.bitsPerPixel;
        this->usingSTBI = other.usingSTBI;

        other.data = nullptr;
    }

    TextureData2D::~TextureData2D() {
        if(usingSTBI)
            stbi_image_free(data);
        else 
            delete[] data;
    }

}