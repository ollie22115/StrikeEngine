#pragma once

#include <array>
#include <string>

#include "Component.h"
#include "Rendering/Vertex.h"
#include "Rendering/Material.h"
#include "Rendering/Colour.h"
#include "RenderableComponent.h"

namespace Strike {

	class SpriteRenderer : public Component, public RenderableComponent {
	public:
		SpriteRenderer(const std::string& shaderPath, const std::string& texturePath = "Default", 
			const uint32_t& x0 = 0, const uint32_t& y0 = 0, const uint32_t& x1 = 1, const uint32_t& y1 = 1,
			const glm::vec4& colour0 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const glm::vec4& colour1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
			const glm::vec4& colour2 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const glm::vec4& colour3 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		inline bool isRenderable() override { return true; }

		std::vector<Vertex> getVertices(const glm::mat4& modelTransform) override;
		inline const Material& getMaterial() { return spriteMaterial; }

		inline uint32_t getWidth() { return  vertices[1].pos.x - vertices[0].pos.x; };
		inline uint32_t getHeight() { return vertices[2].pos.y - vertices[1].pos.y; };

	private:
		std::array<Vertex, 4>  vertices;
		Material spriteMaterial;
	};

}