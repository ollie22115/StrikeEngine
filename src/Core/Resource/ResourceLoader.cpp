#include "StrikePCH.h"

#include "ResourceLoader.h"
#include <stb_image.h>
#include "Utils/FileLoader.h"
#include <cstring>

namespace Strike{

    TextureData2D ResourceLoader::loadTexture2D(const std::string& filePath, const int32_t& desiredBitsPerPixel) {

		if(filePath == "Default")
			return TextureData2D();

		int32_t width, height, bitsPerPixel;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* stbiData = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, desiredBitsPerPixel);

#ifdef STRIKE_DEBUG
		if (!stbiData) Log::logError(LOG_PLATFORM_OPENGL, "stbi Failed to load image");
#endif

		std::unique_ptr<unsigned char[]> tempPtr = 
			std::make_unique<unsigned char[]>(desiredBitsPerPixel * width * height);
		std::memcpy(tempPtr.get(), stbiData, desiredBitsPerPixel * width * height);
		stbi_image_free(stbiData);

		return TextureData2D(tempPtr, width, height, desiredBitsPerPixel);
        
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

    FontData ResourceLoader::loadFontData(const std::string &filePath, 
		const uint32_t &fontSize, const std::string &charactersToGenerate) {
		
		std::unique_ptr<FT_Library> freeTypeHandle = std::make_unique<FT_Library>();
		std::unique_ptr<FT_Face> freeTypeFaceHandle = std::make_unique<FT_Face>();

		STRIKE_ASSERT(!FT_Init_FreeType(freeTypeHandle.get()), LOG_PLATFORM_CORE, 
			"error inititalising freeType Library");
		STRIKE_ASSERT(!FT_New_Face(*freeTypeHandle, filePath.c_str(), 0, freeTypeFaceHandle.get()),
			LOG_PLATFORM_CORE, "FreeType failed to Iniitalise face!");

        return FontData(freeTypeHandle, freeTypeFaceHandle, fontSize, charactersToGenerate);

    }

/*
    MaterialData ResourceLoader::loadMaterialData(const std::string& filePath) {
        //TODO!!!
        
        return MaterialData();
    }
*/




	template<>
	ResourceBuffer ResourceLoader::loadResourceData<Texture2D>(const std::string& filePath){
		ResourceBuffer data = loadTexture2D(filePath);
		return data;
	}

	template<>
    ResourceBuffer ResourceLoader::loadResourceData<Texture2D>(const std::string& filePath, const int32_t& desiredBitsPerPixel){
		ResourceBuffer data = loadTexture2D(filePath, desiredBitsPerPixel);
		return data;
	}

	template<>
    ResourceBuffer ResourceLoader::loadResourceData<Shader>(const std::string& filePath){
		ResourceBuffer data = loadShaderData(filePath);
		return data;
	}

	template<>
    ResourceBuffer ResourceLoader::loadResourceData<Font>(const std::string& filePath, 
        const uint32_t& fontSize, const std::string& charactersToGenerate){

		ResourceBuffer data = loadFontData(filePath, fontSize, charactersToGenerate);
		return data;

	}



	template<>
    void constructEntry(ResourceEntry<Texture2D>& entry, const ResourceBuffer& data,
        const std::string& filePath, const uint32_t& magicNumber){

        entry.construct(filePath, magicNumber, std::get<TextureData2D>(data));
    
    }

    template<>
    void constructEntry(ResourceEntry<Shader>& entry, const ResourceBuffer& data, 
        const std::string& filePath, const uint32_t& magicNumber){

        entry.construct(filePath, magicNumber, std::get<ShaderData>(data));
    }
}