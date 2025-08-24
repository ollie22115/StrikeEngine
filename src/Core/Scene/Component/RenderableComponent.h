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

		SpriteRenderer(const ResourceHandle& shaderHandle, const ResourceHandle& textureHandle, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR) :
				shaderHandle(shaderHandle), textureHandle(textureHandle), 
				colourBL(colourBL), colourBR(colourBR), colourTL(colourTL), colourTR(colourTR) {}; //TODO!!!

		/*
		SpriteRenderer(const std::string& shaderPath, const std::string& textureAtlasPath, const uint32_t& subTextureIndex, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR); //TODO!!!
		*/

		/*
		SpriteRenderer(const ResourceHandle& shaderHandle, const ResourceHandle& textureAtlasHandle, const uint32_t& subTextureIndex, const glm::vec4& colourBL, const glm::vec4& colourBR,
			const glm::vec4& colourTL, const glm::vec4& colourTR); TODO!!!
		*/
		
		//ResourceHandle materialHandle;
		ResourceHandle shaderHandle;
		ResourceHandle textureHandle;
		glm::vec4 colourBL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourBR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct Renderable {
		Renderable() = default;

		std::vector<Vertex> vertices;
		ResourceHandle shaderHandle;
		ResourceHandle textureHandle;
		//ResourceHandle shaderHandle;
		//ResourceHandle textureHandle;

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

	struct EnttMeshRenderer(){
		//TODO!!!
		MeshRenderer() = default;
		MeshRenderer(const MeshRenderer& other) = default;

	};
	
	*/

}