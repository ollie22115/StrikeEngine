#pragma once

#include <string>
#include <initializer_list>
#include <array>
#include <vector>
#include <glm/glm.hpp>

#include "Component.h"
#include "Rendering/Vertex.h"
#include "Rendering/Material.h"
#include "RenderableComponent.h"

namespace Strike {

	//describes a drawable triangle made of Vertex vertices
	struct Triangle {
		std::array<Vertex, 3> vertices;
	};

	class RenderableMesh : public Component, public RenderableComponent {
	public:
		RenderableMesh() : Component(Component::Type::RenderableMesh) {};
		RenderableMesh(std::initializer_list<Triangle> triangles) : Component(Component::Type::RenderableMesh), triangles(triangles) {};

		inline bool isRenderable() override { return true; }

		void addTriangle(const Triangle& triangle);

		std::vector<Vertex> getVertices(const glm::mat4& modelTransform) override;
		inline const Material& getMaterial() { return material; }

		inline uint32_t getVertexCount() { return triangles.size() * 3; }	//number of vertices in mesh
		inline uint32_t getSize() { return getVertexCount() * Vertex::getLayout().size(); } //size in bytes of all mesh vertices combined

	private:
		std::vector<Triangle> triangles;
		Material material;
	};

}