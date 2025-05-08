#include "StrikePCH.h"
#include "RenderableMesh.h"

namespace Strike {

	void RenderableMesh::addTriangle(const Triangle& triangle) {
		triangles.push_back(triangle);
	}

	std::vector<Vertex> RenderableMesh::getVertices(const glm::mat4& modelTransform) {
		std::vector<Vertex> returnVertices;

		for (Triangle& triangle : triangles) for (Vertex& vertex : triangle.vertices) {
			returnVertices.push_back(vertex);
		}

		return returnVertices;
	}

}