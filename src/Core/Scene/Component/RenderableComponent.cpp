#include "StrikePCH.h"
#include "RenderableComponent.h"
#include "Rendering/Renderer.h"

namespace Strike {

    Renderable Renderable::createRenderable(SpriteRenderer &renderableComponent, const Transform &transform) {
        Renderable renderable;
		renderable.materialPtr = renderableComponent.materialPtr;

		Vertex v0(transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), renderableComponent.colourBL);
		Vertex v1(transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), renderableComponent.colourBR);
		Vertex v2(transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), renderableComponent.colourTR);
		Vertex v3(transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), renderableComponent.colourTL);

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
		const glm::vec4& colourTL, const glm::vec4& colourTR) :
		colourBL(colourBL), colourBR(colourBR), colourTL(colourTL), colourTR(colourTR) {
		
		for(ResourcePointer<Material>& matPtr : Renderer::getResourceIterator<Material>()){
			if(matPtr->getShaderPtr() == shaderPtr && matPtr->getTexturePtr() == texturePtr){
				materialPtr = matPtr;
				return;
			}
		}
		
		materialPtr = Renderer::emplaceResource<Material>("SpriteMaterial", shaderPtr, texturePtr);
		
	};
}
