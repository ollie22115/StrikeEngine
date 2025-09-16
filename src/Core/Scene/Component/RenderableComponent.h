#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Transform.h"
#include "Rendering/Vertex.h"
#include "Rendering/Material.h"
#include "Resource/ResourceHandle.h"

#define ALL_RENDERABLE_COMPONENTS MeshRenderer, SpriteRenderer

namespace Strike {

	struct SpriteRenderer {
		SpriteRenderer() = default;
		
		/*
		SpriteRenderer(const std::string& materialPath, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR); //TODO!!!
		*/

		/*
		SpriteRenderer(const ResourceHandle& materialHandle, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR); //TODO!!!
		*/

		/*
		SpriteRenderer(const std::string& shaderPath, const std::string& texturePath, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR); //TODO!!!
		*/

		SpriteRenderer(const ResourceHandle&/*ResourcePointer&*/ shaderHandle, const ResourceHandle&/*ResourcePointer&*/ textureHandle, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR);

		/*
		SpriteRenderer(const std::string& shaderPath, const std::string& textureAtlasPath, const uint32_t& subTextureIndex, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR); //TODO!!!
		*/

		/*
		SpriteRenderer(const ResourceHandle& shaderHandle, const ResourceHandle& textureAtlasHandle, const uint32_t& subTextureIndex, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR); TODO!!!
		*/
		
		ResourceHandle/*ResourcePointer*/ materialHandle;
		ResourceHandle/*ResourcePointer*/ shaderHandle;
		ResourceHandle/*ResourcePointer*/ textureHandle;
		glm::vec4 colourBL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourBR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct Renderable {
		Renderable() = default;

		std::vector<Vertex> vertices;
		ResourceHandle/*ResourcePointer*/ materialHandle;
		ResourceHandle/*ResourcePointer*/ shaderHandle;
		ResourceHandle/*ResourcePointer*/ textureHandle;

		inline std::vector<Vertex>& getVertices() {
			return vertices;
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

	struct MeshRenderer(){
		//TODO!!!
		MeshRenderer() = default;
		MeshRenderer(const MeshRenderer& other) = default;

	};
	
	*/

}