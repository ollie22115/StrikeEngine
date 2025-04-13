#pragma once

#define STRIKE_TEXTURE2D 1

namespace Strike {

	class Texture2D {
	public:
		Texture2D() = default;

		virtual uint32_t width() = 0;
		virtual uint32_t height() = 0;

		virtual void bind() = 0;
	};

}