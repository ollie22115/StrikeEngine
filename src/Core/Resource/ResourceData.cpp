#include "ResourceData.h"
#include <stb_image.h>

namespace Strike{

    TextureData2D::~TextureData2D() {
        stbi_image_free(data);
    }

}