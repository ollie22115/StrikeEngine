#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Transform.h"
#include "Rendering/Vertex.h"
#include "Rendering/Material.h"

#define ALL_RENDERABLE_COMPONENTS MeshRenderer, SpriteRenderer

namespace Strike {

	struct SpriteRenderer {
		SpriteRenderer() = default;
		SpriteRenderer(const Material& material, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR) : 
			material(material), colourBL(colourBL), colourBR(colourBR), colourTL(colourTL), colourTR(colourTR) {};
		SpriteRenderer(const std::string& texturePath, const std::string& shaderPath, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR) :
			material(texturePath, shaderPath), colourBL(colourBL), colourBR(colourBR), colourTL(colourTL), colourTR(colourTR) {};
		SpriteRenderer(SpriteRenderer & other) = default;

		Material material;
		glm::vec4 colourBL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourBR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct Renderable {
		Renderable() = default;

		std::vector<Vertex> vertices;
		Material* material = nullptr;

		inline std::vector<Vertex>& getVertices() {
			return vertices;
		}

		inline Material& getMaterial() {
			return *material;
		}

		inline bool isRenderable() { return vertices.size() != 0; }

		/*
		static Renderable createRenderable(const MeshRenderer& renderableComponent, const Transform& transform) {
			//TODO!!!
		}
		*/

		static Renderable createRenderable(SpriteRenderer& renderableComponent, const Transform& transform);

		static Renderable createNonRenderable();
	};

	/*

	struct EnttMeshRenderer(){
		//TODO!!!
		MeshRenderer() = default;
		MeshRenderer(const MeshRenderer& other) = default;

	};
	
	*/

}