#include "StrikePCH.h"
#include "Vertex.h"

namespace Strike {

	VertexAttribute::VertexAttribute(Type type, bool normalised) : type(type), count(0), normalised(normalised) {
		switch (type) {
		case Type::Float:
			count = 1;
			break;

		case Type::Float2:
			count = 2;
			break;

		case Type::Float3:
			count = 3;
			break;

		case Type::Float4:
			count = 4;
			break;
		}

	}

	uint32_t VertexAttribute::size() const {

		switch (type) {
		case Type::Float:
			return 4;

		case Type::Float2:
			return 4 * count;

		case Type::Float3:
			return 4 * count;

		case Type::Float4:
			return 4 * count;
		}

	}

	uint32_t VertexLayout::count() {
		uint32_t count = 0;
		for (const VertexAttribute& attribute : attributes)
			count += attribute.count;

		return count;
	}

	uint32_t VertexLayout::size() {
		uint32_t size = 0;
		for (const VertexAttribute& attribute : attributes)
			size += attribute.size();

		return size;
	}

	bool Vertex::operator==(const Vertex& other) const {
		return pos == other.pos && texCoords == other.texCoords && colour == other.colour;
	}
}
