#include "StrikePCH.h"

#include "ResourceLoader.h"
#include <stb_image.h>
#include "Utils/FileLoader.h"

namespace Strike{

    TextureData2D ResourceLoader::loadTexture2D(const std::string& filePath) {

		int32_t width, height, bitsPerPixel;
        int32_t desiredBitsPerPixel = 4;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, desiredBitsPerPixel);

#ifdef STRIKE_DEBUG
		if (!data) Log::logError(LOG_PLATFORM_OPENGL, "stbi Failed to load image");
#endif

        return TextureData2D(data, width, height, bitsPerPixel);
        
    }

/*
    TextureAtlasData ResourceLoader::loadTextureAtlas(const std::string& filePath) {
        //TODO!!!
        
        return TextureAtlasData();
    }
*/

    ShaderData ResourceLoader::loadShaderData(const std::string& filePath) {
        std::string src = FileLoader::loadTextFile(filePath);

        std::stringstream srcStream;
		srcStream << src;
		std::stringstream vertexShaderSrc;
		std::stringstream pixelShaderSrc;
		std::string line;
		uint32_t shaderType = 0;	//0 = none, 1 = vertex, 2 = pixel
		while (getline(srcStream, line)) {
			if (line.find("#type vertex") != std::string::npos)
				shaderType = 1;
			else if (line.find("#type pixel") != std::string::npos)
				shaderType = 2;
			else {
				STRIKE_ASSERT(shaderType > 0 && shaderType < 3, LOG_PLATFORM_OPENGL, "Error shader source must have a type");

				switch (shaderType) {
					case 1:
						vertexShaderSrc << line << "\n";
						break;

					case 2:
						pixelShaderSrc << line << "\n";
						break;
				}
			}
		}
        
        return ShaderData(vertexShaderSrc.str(), pixelShaderSrc.str());
    }

/*
    MaterialData ResourceLoader::loadMaterialData(const std::string& filePath) {
        //TODO!!!
        
        return MaterialData();
    }
*/

}