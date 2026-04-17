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

		renderable.vertices.reserve(6);
		renderable.vertices.push_back(v0);
		renderable.vertices.push_back(v1);
		renderable.vertices.push_back(v2);
		renderable.vertices.push_back(v0);
		renderable.vertices.push_back(v2);
		renderable.vertices.push_back(v3);

		return renderable;
    }

	/* TODO!!!
	std::vector<Renderable> Renderable::createRenderable(const FontRenderer& renderableComponent, const Transform& transform) {
		std::vector<Renderable> renderables;
		renderables.reserve(renderableComponent.glyphs.size());

		uint32_t width = 0;
		uint32_t height = 0;
		for(const auto& glyphRenderer : renderableComponent.glyphs) {
			width += glyphRenderer.advance;
			height = (height < glyphRenderer.height) ? glyphRenderer.height : height;
		}

		uint32_t penX = -width / 2;
		uint32_t penY = -height / 2;
		for(const auto& glyphRenderer : renderableComponent.glyphs) {
			const glm::vec4& textureCoords = glyphRenderer.materialPtr->getTextureCoords();

			renderables.emplace_back();
			Renderable& renderable = renderables.back();
			renderable.materialPtr = glyphRenderer.materialPtr;
			
			glm::vec4 posBL = transform * glm::vec4(penX + glyphRenderer.bearingX, penY - (glyphRenderer.height - glyphRenderer.bearingY), 0, 0);
			glm::vec4 posBR = transform * glm::vec4(penX + glyphRenderer.bearingX + glyphRenderer.width, penY - (glyphRenderer.height - glyphRenderer.bearingY), 0, 0);
			glm::vec4 posTL = transform * glm::vec4(penX + glyphRenderer.bearingX, penY + glyphRenderer.bearingY, 0, 0);
			glm::vec4 posTR = transform * glm::vec4(penX + glyphRenderer.bearingX + glyphRenderer.width, penY + glyphRenderer.bearingY, 0, 0);

			glm::vec2 texCoordsBL = glm::vec2(textureCoords[0], textureCoords[1]);
			glm::vec2 texCoordsBR = glm::vec2(textureCoords[2], textureCoords[1]);
			glm::vec2 texCoordsTL = glm::vec2(textureCoords[0], textureCoords[3]);
			glm::vec2 texCoordsTR = glm::vec2(textureCoords[2], textureCoords[3]);

			Vertex v0(posBL, texCoordsBL, renderableComponent.colourBL);
			Vertex v1(posBR, texCoordsBR, renderableComponent.colourBR);
			Vertex v2(posTR, texCoordsTR, renderableComponent.colourTR);
			Vertex v3(posTL, texCoordsTL, renderableComponent.colourTL);

			renderable.vertices.reserve(6);
			renderable.vertices.push_back(v0);
			renderable.vertices.push_back(v1);
			renderable.vertices.push_back(v2);
			renderable.vertices.push_back(v0);
			renderable.vertices.push_back(v2);
			renderable.vertices.push_back(v3);

			penX += glyphRenderer.advance;
		}

		return renderables;
	}
	*/

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
		glm::vec4 textureCoords = subTexture.textureCoords;	
		
		for(ResourcePointer<Material>& matPtr : Renderer::getResourceIterator<Material>()){
			if(matPtr->getShaderPtr() == shaderPtr && matPtr->getTexturePtr() == textureAtlasPtr->getTexture() && matPtr->getTextureCoords() == textureCoords){
				materialPtr = matPtr;
				return;
			}
		}
		materialPtr = Renderer::emplaceResource<Material>("SpriteMaterial", shaderPtr, textureAtlasPtr->getTexture(), textureCoords);

	};



    FontRenderer::GlyphRenderer::GlyphRenderer(const ResourcePointer<Shader> &shaderPtr, const ResourcePointer<Font> &fontPtr, const char &character) {
		auto& glyph = fontPtr->getGlyph(character);
		glm::vec4 textureCoords = glyph.getTextureCoords();

		bearingX = glyph.bearingX;
		bearingY = glyph.bearingY;
		advance = glyph.advance;
		width = glyph.width;
		height = glyph.height;

		for(ResourcePointer<Material>& matPtr : Renderer::getResourceIterator<Material>()) {
			if(matPtr->getShaderPtr() == shaderPtr && matPtr->getTexturePtr() == glyph.getTexture() && matPtr->getTextureCoords() == textureCoords){
				materialPtr = matPtr;
				return;
			}
		}

		materialPtr = Renderer::emplaceResource<Material>("", shaderPtr, glyph.getTexture(), textureCoords);
    }

    FontRenderer::FontRenderer(const ResourcePointer<Font> &fontPtr, const ResourcePointer<Shader> &shaderPtr, const std::string &text, const glm::vec4 &colour) : colour(colour) {
		glyphs.reserve(text.size());
		for(const char& c : text) 
			glyphs.emplace_back(shaderPtr, fontPtr, c);
	}

}
