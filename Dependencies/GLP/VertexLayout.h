#pragma once
#include <glad/glad.h>
#include <vector>


namespace GLP {

	struct VertexAttribute {
		GLenum type;
		GLenum normalised;
		unsigned int count;

		VertexAttribute(GLenum type, GLenum normalised, unsigned int count) : type(type), normalised(normalised), count(count) {};
		int getSize();
	};

	struct VertexLayout {
		std::vector<VertexAttribute> attributes;
		uint32_t size = 0;

		void pushAttribute(GLenum type, GLenum normalised, unsigned int count);
	};

}