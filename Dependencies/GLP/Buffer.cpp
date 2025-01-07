#include "Buffer.h"

void Buffer::init(){
	glGenBuffers(1, &id);
}

void Buffer::bind(){
	glBindBuffer(target, id);
}

Buffer::~Buffer(){
	glDeleteBuffers(1, &id);
}

void VertexBuffer::pushAttribute(GLenum type, GLenum normalised, unsigned int count){
	attributes.emplace_back(type, normalised, count);
	size += attributes[attributes.size() - 1].getSize() * count;
}

void VertexBuffer::initAttributes(){
	int index = 0;
	int pointer = 0;

	for (VertexAttribute& attribute : attributes) {
		glVertexAttribPointer(index, attribute.count, attribute.type, attribute.normalised, size, (void*)pointer);
		glEnableVertexAttribArray(index);

		pointer += attribute.getSize() * attribute.count;
		index++;
	}
}

int VertexBuffer::VertexAttribute::getSize() {
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
