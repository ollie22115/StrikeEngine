#include "VertexLayout.h"

int VertexAttribute::getSize() {
	switch (type) {
		case GL_FLOAT:
			return sizeof(GLfloat);
			break;

		case GL_INT:
			return sizeof(GLint);
			break;

		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
			break;
	}

	return 0;
}

void VertexLayout::pushAttribute(GLenum type, GLenum normalised, unsigned int count)
{
	attributes.emplace_back(type, normalised, count);
	size += attributes[attributes.size() - 1].getSize() * count;
}
