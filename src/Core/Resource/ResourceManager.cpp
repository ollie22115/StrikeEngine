#include "ResourceManager.h"

namespace Strike{

    template<>
    ResourceHandle/*ResourcePointer*/ ResourceManager<Texture2D>::load(const std::string& filePath){

        for(size_t i = 0; i < resourcePool.size(); i++){
            Entry& entry = resourcePool[i];
            if(entry.inUse() && entry.getFilePath() == filePath)
                return constructHandle(i + 1, entry.getMagicNumber());
        }
        /*for(size_t i = 0; i < resourcePool.size(); i++){
            Entry& entry = resourcePool[i];
            if(entry.inUse() && entry.getFilePath() == filePath){
                entry.refCount++;
                return ResourcePointer(constructHandle(i + 1, entry.getMagicNumber()), this);
            }
        }*/

        ResourceHandle handle = getHandleFromFilePath(filePath);

        if(filePath == "Default")
            resourcePool[getPosition(handle) - 1].construct(filePath, getMagicNumber(handle));
        else{
            TextureData2D textureData = ResourceLoader::loadTexture2D(filePath);

            resourcePool[getPosition(handle) - 1].construct(filePath, getMagicNumber(handle), textureData);
        }
        
        return handle;
        /*return ResourcePointer(handle, this);*/

    }

    template<>
    ResourceHandle/*ResourcePointer*/ ResourceManager<Shader>::load(const std::string& filePath){

        for(size_t i = 0; i < resourcePool.size(); i++){
            Entry& entry = resourcePool[i];
            if(entry.inUse() && entry.getFilePath() == filePath)
                return constructHandle(i + 1, entry.getMagicNumber());
        }
        /*for(size_t i = 0; i < resourcePool.size(); i++){
            Entry& entry = resourcePool[i];
            if(entry.inUse() && entry.getFilePath() == filePath){
                entry.refCount++;
                return ResourcePointer(constructHandle(i + 1, entry.getMagicNumber()), this);
            }
        }*/

        ResourceHandle handle = getHandleFromFilePath(filePath);

        if(filePath.c_str() == "Default"){
            STRIKE_ASSERT(false, LOG_PLATFORM_OPENGL, "Default shader not implemented yet");
        } else{
            ShaderData shaderData = ResourceLoader::loadShaderData(filePath);

            resourcePool[getPosition(handle) - 1].construct(filePath, getMagicNumber(handle), shaderData);
        }

        return handle;
        /*return ResourcePointer(handle, this);*/

    }
}