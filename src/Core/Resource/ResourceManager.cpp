#include "ResourceManager.h"

namespace Strike{

    template<>
    ResourceHandle ResourceManager<Texture2D>::load(const std::string& filePath){
        for(auto& entry : resourceMap) if(entry.second.getFilePath() == filePath)
            return constructHandle(entry.first, entry.second.getMagicNumber());
            //return entry.first;

        ResourceHandle handle = getHandleFromFilePath(filePath);

        if(filePath == "Default")
            //resourceMap.emplace(std::piecewise_construct, std::forward_as_tuple(handle), std::forward_as_tuple(filePath));
            resourceMap.emplace(std::piecewise_construct, std::forward_as_tuple(getPosition(handle)), std::forward_as_tuple(filePath, getMagicNumber(handle)));
        else{
            TextureData2D textureData = ResourceLoader::loadTexture2D(filePath);

            //resourceMap.emplace(std::piecewise_construct, std::forward_as_tuple(handle), std::forward_as_tuple(filePath, textureData));
            resourceMap.emplace(std::piecewise_construct, std::forward_as_tuple(getPosition(handle)), std::forward_as_tuple(filePath, getMagicNumber(handle), textureData));
        }
        
        return handle;
    }

    template<>
    ResourceHandle ResourceManager<Shader>::load(const std::string& filePath){
        for(auto& entry : resourceMap) if(entry.second.getFilePath() == filePath)
            return constructHandle(entry.first, entry.second.getMagicNumber());
            //return entry.first;

        ResourceHandle handle = getHandleFromFilePath(filePath);

        if(filePath.c_str() == "Default"){
            STRIKE_ASSERT(false, LOG_PLATFORM_OPENGL, "Default shader not implemented yet");
            //resourceMap[handle] = Shader();
        } else{
            ShaderData shaderData = ResourceLoader::loadShaderData(filePath);

            //resourceMap.emplace(std::piecewise_construct, std::forward_as_tuple(handle), std::forward_as_tuple(filePath, shaderData));
            resourceMap.emplace(std::piecewise_construct, std::forward_as_tuple(getPosition(handle)), std::forward_as_tuple(filePath, getMagicNumber(handle), shaderData));
        }

        return handle;
    }
}