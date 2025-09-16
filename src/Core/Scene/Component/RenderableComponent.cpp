#include "StrikePCH.h"
#include "RenderableComponent.h"
#include "Rendering/Renderer.h"

namespace Strike {
	

    Renderable Renderable::createRenderable(SpriteRenderer &renderableComponent, const Transform &transform) {
        Renderable renderable;
		renderable.shaderHandle = renderableComponent.shaderHandle;
		renderable.textureHandle = renderableComponent.textureHandle;
		renderable.materialHandle = renderableComponent.materialHandle;

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

	/*
    SpriteRenderer::SpriteRenderer(const std::string &materialPath, 
		const glm::vec4 &colourBL, const glm::vec4 &colourBR, const glm::vec4 &colourTL, const glm::vec4 &colourTR) :
		colourBL(colourBL), colourBR(colourBR), colourTL(colourTL), colourTR(colourTR) {
		//ResourceHandle materialHandle = Renderer::loadResource<Material>(materialPath);
		//this->materialHandle = materialHandle;
    }
	*/

	/*
    SpriteRenderer::SpriteRenderer(const std::string &shaderPath, const std::string &texturePath, 
		const glm::vec4 &colourBL, const glm::vec4 &colourBR, const glm::vec4 &colourTL, const glm::vec4 &colourTR) :
		colourBL(colourBL), colourBR(colourBR), colourTL(colourTL), colourTR(colourTR) {
		//TODO!!!

        ResourceHandle shaderHandle = Renderer::loadResource<Shader>(shaderPath);
		ResourceHandle textureHandle = Renderer::loadResource<Texture2D>(texturePath);

		// ROUGH DRAFT
		Material* material = nullptr;
		for(Material* mat : Renderer::iterateResources<Texture2D>()){
			if(mat->textureHandle == textureHandle && mat->shaderHandle == shaderHandle){
				material = mat;
				break;
			}
		}
		if(!materialHandle)
			Renderer::createResource(shaderHandle, textureHandle);
		
		//
    }
	*/
    SpriteRenderer::SpriteRenderer(const ResourceHandle&/*ResourcePointer&*/ shaderHandle, const ResourceHandle&/*ResourcePointer&*/ textureHandle, 
		const glm::vec4& colourBL, const glm::vec4& colourBR,
		const glm::vec4& colourTL, const glm::vec4& colourTR) :
		shaderHandle(shaderHandle), textureHandle(textureHandle), 
		colourBL(colourBL), colourBR(colourBR), colourTL(colourTL), colourTR(colourTR) {
		
		//TODO!!! Change this later it's very hacky
		uint32_t materialIndex = 1;
		for(auto& entry : Renderer::getResourceIterator<Material>()){
			if(!entry.inUse()) continue;
			if(entry.getResource().getShaderHandle() == shaderHandle && entry.getResource().getTextureHandle() == textureHandle){
				materialHandle = constructHandle(materialIndex, entry.getMagicNumber());
				return;
			}

			materialIndex++;
		}
		//////////////////////////////////////////////////
		
		materialHandle = Renderer::emplaceResource<Material>("SpriteMaterial", shaderHandle, textureHandle);
		
	};
}
