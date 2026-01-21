#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Transform.h"
#include "Rendering/Vertex.h"
#include "Rendering/Material.h"
#include "Rendering/TextureAtlas.h"
#include "Resource/ResourceHandle.h"

#define ALL_RENDERABLE_COMPONENTS MeshRenderer, SpriteRenderer

namespace Strike {

	struct SpriteRenderer {
		SpriteRenderer() = default;

		SpriteRenderer(const ResourcePointer<Shader>& shaderPtr, const ResourcePointer<Texture2D>& texturePtr, const glm::vec4& colourBL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const glm::vec4& colourBR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			const glm::vec4& colourTL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const glm::vec4& colourTR= glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 
			const glm::vec4& textureCoords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		SpriteRenderer(const ResourcePointer<Shader>& shaderPtr, const ResourcePointer<TextureAtlas>& textureAtlasPtr, const int32_t& textureIndex, 
			const glm::vec4& colourBL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const glm::vec4& colourBR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
			const glm::vec4& colourTL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), const glm::vec4& colourTR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		/*SpriteRenderer(const ResourcePointer<Material>& materialPtr, 
			const glm::vec4& colourBL, const glm::vec4& colourBR, const glm::vec4& colourTL, const glm::vec4& colourTR);*/
		
		ResourcePointer<Material> materialPtr;
		glm::vec4 colourBL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourBR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTL = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 colourTR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	};

	struct Renderable {
		Renderable() = default;

		std::vector<Vertex> vertices;
		ResourcePointer<Material> materialPtr;

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