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



void VertexBuffer::initAttributes(VertexLayout& vertexLayout){
	int index = 0;
	int pointer = 0;

	for (VertexAttribute& attribute : vertexLayout.attributes) {
		glVertexAttribPointer(index, attribute.count, attribute.type, attribute.normalised, vertexLayout.size, (void*)pointer);
		glEnableVertexAttribArray(index);

		pointer += attribute.getSize() * attribute.count;
		index++;
	}
}
