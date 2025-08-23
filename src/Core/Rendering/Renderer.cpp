#include "StrikePCH.h"
#include "Renderer.h"

#ifdef STRIKE_OPENGL
#include "../Platforms/OpenGL/GLRenderer.h"
#endif

namespace Strike {
	
	ResourceManager<Texture2D> Renderer::textureManager;
	ResourceManager<Shader> Renderer::shaderManager;

	std::unique_ptr<Renderer> Strike::Renderer::createRenderer() {
#ifdef STRIKE_DEBUG
		uint32_t totalRendererAPISet = 0;

#ifdef STRIKE_OPENGL
		totalRendererAPISet++;
#endif
		//include other rendering API's when necessary
		STRIKE_ASSERT(totalRendererAPISet < 2, LOG_PLATFORM_CORE, "Cannot have more than one renderer API set at once!");
		
#endif

		switch (platform) {
			case RendererPlatform::None:
				STRIKE_ASSERT(false, LOG_PLATFORM_CORE, "No Renderer API bound!");
				break;

			case RendererPlatform::OpenGL:
				return std::make_unique<GLRenderer>();

			case RendererPlatform::DirectX:
				STRIKE_ASSERT(false, LOG_PLATFORM_CORE, "DirectX11 is not supported yet!");
				break;
		}
	}

	template<>
	ResourceHandle Renderer::loadResource<Texture2D>(const std::string& filePath) {
		return textureManager.load(filePath);
	}

	template<>
	Texture2D* Renderer::getResource<Texture2D>(const ResourceHandle& handle) {
		return textureManager.get(handle);
	}

	template<>
	ResourceHandle Renderer::loadResource<Shader>(const std::string& filePath){
		return shaderManager.load(filePath);
	}

	template<>
	Shader* Renderer::getResource<Shader>(const ResourceHandle& filePath){
		return shaderManager.get(filePath);
	}

	Renderer::~Renderer(){
		textureManager.clear();
		shaderManager.clear();
		//textureAtlasManager.clear();
		//materialManager.clear();
	}
}
