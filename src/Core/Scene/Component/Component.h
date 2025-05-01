#pragma once

namespace Strike {
	
	class Component {
	public:
		enum class Type {
			None = 0, RenderableMesh, SpriteRenderer, Camera
		};

		inline Component(const Type& type) : type(type) {};

		inline Type getType() const { return type; }

		virtual bool isRenderable() = 0;

	private:
		Type type;

	};

}