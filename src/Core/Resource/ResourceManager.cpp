#include "ResourceManager.h"

namespace Strike{

    template<>
    ResourceHandle ResourceManager<Texture2D>::load(const std::string& filePath){
        //TODO!!!
        if(resourceMap.find(filePath) != resourceMap.end())
            return filePath;

        ResourceHandle handle = getHandleFromFilePath(filePath);   //change when switching to uint32_t handles

        if(filePath == "Default")
            resourceMap[handle] = Texture2D();
        else{
            //TextureData2D textureData = ResourceLoader::loadTexture2D(filePath);

            //resourceMap.emplace(handle, textureData);
        }

        std::cout << "Working!\n";
        return handle;
    }

    template<>
    ResourceHandle ResourceManager<Shader>::load(const std::string& filePath){
        if(resourceMap.find(filePath) != resourceMap.end())
            return filePath;

        ResourceHandle handle = getHandleFromFilePath(filePath);   //change when switching to uint32_t handles

        if(filePath.c_str() == "Default"){
            STRIKE_ASSERT(false, LOG_PLATFORM_OPENGL, "Default shader not implemented yet");
            //resourceMap[handle] = Shader();
        } else{
            ShaderData shaderData = ResourceLoader::loadShaderData(filePath);

            resourceMap.emplace(handle, shaderData);
        }

        return handle;
    }
}