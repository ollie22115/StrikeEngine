#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Rendering/Vertex.h"
#include "Rendering/Material.h"

#define ALL_RENDERABLE_COMPONENTS MeshRenderer, SpriteRenderer

namespace Strike {

	/*

	struct MeshRenderer(){
		//TODO!!!
		MeshRenderer() = default;
		MeshRenderer(const MeshRenderer& other) = default;

	};

	struct SpriteRenderer(){
		SpriteRenderer() = default;
		SpriteRenderer(SpriteRenderer& other) = default;

		std::string shaderPath = "Default";
		std::string texturePath = "Default";
		glm::vec4 colourBL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourBR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	};
	
	*/

	class RenderableComponent {
	public:
		virtual std::vector<Vertex> getVertices(const glm::mat4& modelTransform) = 0;
		virtual const Material& getMaterial() = 0;
	};

}