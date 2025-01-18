#include "Buffer.h"

void GLP::Buffer::init(){
	glGenBuffers(1, &id);
}

void GLP::Buffer::bind(){
	glBindBuffer(target, id);
}

GLP::Buffer::~Buffer(){
	glDeleteBuffers(1, &id);
}



void GLP::VertexBuffer::initAttributes(VertexLayout& vertexLayout){
	int index = 0;
	int pointer = 0;

	for (VertexAttribute& attribute : vertexLayout.attributes) {
		glVertexAttribPointer(index, attribute.count, attribute.type, attribute.normalised, vertexLayout.size, (void*)pointer);
		glEnableVertexAttribArray(index);

		pointer += attribute.getSize() * attribute.count;
		index++;
	}
}
