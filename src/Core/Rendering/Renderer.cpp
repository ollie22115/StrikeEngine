#include "StrikePCH.h"
#include "Renderer.h"

#ifdef STRIKE_OPENGL
#include "../Platforms/OpenGL/GLRenderer.h"
#endif

namespace Strike {

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

}
