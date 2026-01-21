#include "StrikePCH.h"
#include "RenderableComponent.h"
#include "Rendering/Renderer.h"

namespace Strike {

    Renderable Renderable::createRenderable(SpriteRenderer &renderableComponent, const Transform &transform) {
        Renderable renderable;
		renderable.materialPtr = renderableComponent.materialPtr;

		glm::vec2 texCoordsBL = glm::vec2(renderableComponent.materialPtr->getTextureCoords()[0], 
			renderableComponent.materialPtr->getTextureCoords()[1]);
		glm::vec2 texCoordsBR = glm::vec2(renderableComponent.materialPtr->getTextureCoords()[2], 
			renderableComponent.materialPtr->getTextureCoords()[1]);
		glm::vec2 texCoordsTL = glm::vec2(renderableComponent.materialPtr->getTextureCoords()[0], 
			renderableComponent.materialPtr->getTextureCoords()[3]);
		glm::vec2 texCoordsTR = glm::vec2(renderableComponent.materialPtr->getTextureCoords()[2], 
			renderableComponent.materialPtr->getTextureCoords()[3]);
		Vertex v0(transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), texCoordsBL, renderableComponent.colourBL);
		Vertex v1(transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f), texCoordsBR, renderableComponent.colourBR);
		Vertex v2(transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f), texCoordsTR, renderableComponent.colourTR);
		Vertex v3(transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f), texCoordsTL, renderableComponent.colourTL);

		renderable.vertices.push_back(v0);
		renderable.vertices.push_back(v1);
		renderable.vertices.push_back(v2);
		renderable.vertices.push_back(v0);
		renderable.vertices.push_back(v2);
		renderable.vertices.push_back(v3);

		return renderable;
    }

    Renderable Renderable::createNonRenderable() {
		Renderable nonRenderable;
		return nonRenderable;
	}

    SpriteRenderer::SpriteRenderer(const ResourcePointer<Shader>& shaderPtr, const ResourcePointer<Texture2D>& texturePtr, 
		const glm::vec4& colourBL, const glm::vec4& colourBR,
		const glm::vec4& colourTL, const glm::vec4& colourTR, const glm::vec4& textureCoords) :
		colourBL(colourBL), colourBR(colourBR), colourTL(colourTL), colourTR(colourTR) {
		
		for(ResourcePointer<Material>& matPtr : Renderer::getResourceIterator<Material>()){
			if(matPtr->getShaderPtr() == shaderPtr && matPtr->getTexturePtr() == texturePtr && matPtr->getTextureCoords() == textureCoords){
				materialPtr = matPtr;
				return;
			}
		}

		materialPtr = Renderer::emplaceResource<Material>("SpriteMaterial", shaderPtr, texturePtr, textureCoords);

	}
    SpriteRenderer::SpriteRenderer(const ResourcePointer<Shader> &shaderPtr, const ResourcePointer<TextureAtlas> &textureAtlasPtr, const int32_t &textureIndex, 
		const glm::vec4 &colourBL, const glm::vec4 &colourBR, const glm::vec4 &colourTL, const glm::vec4 &colourTR) {
    
		const TextureAtlas::SubTexture& subTexture = textureAtlasPtr->getSubTexture(textureIndex);
		glm::vec4 textureCoords = glm::vec4(subTexture.u0, subTexture.v0, subTexture.u1, subTexture.v1);
			
		
		for(ResourcePointer<Material>& matPtr : Renderer::getResourceIterator<Material>()){
			if(matPtr->getShaderPtr() == shaderPtr && matPtr->getTexturePtr() == textureAtlasPtr->getTexture() && matPtr->getTextureCoords() == textureCoords){
				materialPtr = matPtr;
				return;
			}
		}
		materialPtr = Renderer::emplaceResource<Material>("SpriteMaterial", shaderPtr, textureAtlasPtr->getTexture(), textureCoords);

	};


}
