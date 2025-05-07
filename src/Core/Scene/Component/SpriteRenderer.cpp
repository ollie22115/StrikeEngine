#include "StrikePCH.h"
#include "SpriteRenderer.h"
#include "Utils/FileLoader.h"

namespace Strike {
	SpriteRenderer::SpriteRenderer(const std::string& shaderPath, const std::string& texturePath, const uint32_t& x0, const uint32_t& y0, const uint32_t& x1, const uint32_t& y1,
		const glm::vec4& colour0, const glm::vec4& colour1, const glm::vec4& colour2, const glm::vec4& colour3) : Component(Component::Type::SpriteRenderer) {

		uint32_t width, height;
		if (texturePath == "Default") {
			width = 1;
			height = 1;
		} else 
			FileLoader::getTextureDimensions(texturePath, width, height);

		vertices[0] = Vertex(glm::vec4( -(width / 2.0f), -(height / 2.0f), 0.0f, 1.0f), glm::vec2(x0, y0), colour0);
		vertices[1] = Vertex(glm::vec4(width/2.0f, -(height/2.0f), 0.0f, 1.0f), glm::vec2(x1, y0), colour1);
		vertices[2] = Vertex(glm::vec4(width/2.0f, height/2.0f, 0.0f, 1.0f), glm::vec2(x1, y1), colour2);
		vertices[3] = Vertex(glm::vec4(-(width/2.0f), height/2.0f, 0.0f, 1.0f), glm::vec2(x0, y1), colour3);

		spriteMaterial = { texturePath, shaderPath };
	}

	std::vector<Vertex> Strike::SpriteRenderer::getVertices(const glm::mat4& modelTransform) {
		std::vector<Vertex> returnVertices;
		
		Vertex v0 = vertices[0];
		v0.pos = modelTransform * v0.pos;
		Vertex v1 = vertices[1];
		v1.pos = modelTransform * v1.pos;
		Vertex v2 = vertices[2];
		v2.pos = modelTransform * v2.pos;
		Vertex v3 = vertices[3];
		v3.pos = modelTransform * v3.pos;

		returnVertices.push_back(v0);
		returnVertices.push_back(v1);
		returnVertices.push_back(v2);
		returnVertices.push_back(v0);
		returnVertices.push_back(v2);
		returnVertices.push_back(v3);
		
		return returnVertices;
	}
}
