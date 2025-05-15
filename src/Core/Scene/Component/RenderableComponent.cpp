#include "StrikePCH.h"
#include "RenderableComponent.h"

namespace Strike {
	
	Renderable Renderable::createRenderable(SpriteRenderer& renderableComponent, const Transform& transform) {
		Renderable renderable;
		renderable.material = &renderableComponent.material;

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

}
