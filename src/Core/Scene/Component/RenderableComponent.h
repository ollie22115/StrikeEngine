#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Rendering/Vertex.h"
#include "Rendering/Material.h"

namespace Strike {

	class RenderableComponent {
	public:
		virtual std::vector<Vertex> getVertices(const glm::mat4& modelTransform) = 0;
		virtual const Material& getMaterial() = 0;
	};

}