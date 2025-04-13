#pragma once

#include <glm/glm.hpp>

namespace Strike {
	
	struct VertexAttribute {
		enum class Type {
			Float, Float2, Float3, Float4
			//TODO!!! Add more types (such as int and uint)
		};

		Type type;
		uint32_t count;
		bool normalised;

		uint32_t size() const;

		VertexAttribute(Type type, bool normalised);
	};

	struct VertexLayout {
		std::vector<VertexAttribute> attributes;

		VertexLayout(const std::initializer_list<VertexAttribute>& attributes) : attributes(attributes) {}

		uint32_t count();	//number of elements in each vertex
		uint32_t size();		//size of each vertex in bytes
	};

	struct Vertex {
		glm::vec4 pos;
		glm::vec2 texCoords = glm::vec2(0.0f, 0.0f);
		glm::vec4 colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		Vertex() = default;

		inline Vertex(const glm::vec4& pos, const glm::vec2& texCoords = glm::vec2(0.0f, 0.0f), const glm::vec4& colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) :
			pos(pos), texCoords(texCoords), colour(colour) {
		};

		inline static VertexLayout getLayout() {
			return VertexLayout({
					{VertexAttribute::Type::Float4, false},
					{VertexAttribute::Type::Float2, false},
					{VertexAttribute::Type::Float4, false}
				});
		}

		bool operator ==(const Vertex& other);
	};

}