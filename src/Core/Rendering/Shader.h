#pragma once

#define STRIKE_SHADER_VERTEX		1
#define STRIKE_SHADER_PIXEL			2

namespace Strike {

	class VertexShader{
	public:
		VertexShader() = default;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual ~VertexShader() = 0;
	};

	class PixelShader{
	public:
		PixelShader() = default;

		virtual void bind() = 0;
		virtual void unBind() = 0;

		virtual ~PixelShader() = 0;
	};
}