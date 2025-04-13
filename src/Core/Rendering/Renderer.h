#pragma once

#include "Debugging/StrikeDebug.h"

#include "Scene/Scene.h"
#include "Shader.h"
#include "Window.h"

//TODO!!! BAD CODE REPLACE LATER
#define STRIKE_OPENGL

namespace Strike {

	//TODO!!! Unused, use to implement batch rendering
	struct RendererCommand {
		enum CommandType {
			None = 0, DrawIndexed
		};

		CommandType type;
		uint32_t offset;
		uint32_t count;

		RendererCommand(const CommandType& type, const uint32_t& offset, const uint32_t count) :
			type(type), offset(offset), count(count) {}
	};

	class Renderer {
	public:
		enum class RendererPlatform {
			None = 0, OpenGL, DirectX
		};

		Renderer() = default;

		static std::unique_ptr<Renderer> createRenderer();

		inline static RendererPlatform getRendererPlatform() { return platform; }

		virtual void init(const std::shared_ptr<Window>& window) = 0;
		
		virtual void swapBuffers(const std::shared_ptr<Window>& window) = 0;

		///virtual void setVertexLayout(const VertexLayout& layout) = 0;	//for now vertex layout will be set for all vertex buffers

		virtual void loadScene(std::shared_ptr<Scene>& scene) = 0;

		virtual void draw(std::shared_ptr<Window>& window) = 0;

		virtual void update() = 0;

		//virtual void clearData() = 0;

		//virtual ~Renderer() = 0;

	private:
#if defined(STRIKE_OPENGL)
		const static RendererPlatform platform = RendererPlatform::OpenGL;
#elif defined(STRIKE_DIRECTX)
		const static RendererPlatform platform = RendererPlatform::DirectX;
#else
		const static RendererPlatform platform = RendererPlatform::None;
#endif
	};

}