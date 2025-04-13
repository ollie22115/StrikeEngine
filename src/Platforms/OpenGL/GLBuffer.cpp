#include "StrikePCH.h"
#include "GLBuffer.h"

namespace Strike {
	
	GLVertexBuffer::GLVertexBuffer() : id(0) {
		glGenBuffers(1, &id);
	}

	void GLVertexBuffer::bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void GLVertexBuffer::unBind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GLVertexBuffer::setData(const uint32_t& size, void* data, uint32_t usage) {
		bind();

		glBufferData(GL_ARRAY_BUFFER, (int)size, data, usage);
	}

	void GLVertexBuffer::setVertexLayout(const VertexLayout& vertexLayout) {
		int index = 0;
		int pointer = 0;

		bind();

		uint32_t vertexSize = 0;
		for (const VertexAttribute& attribute : vertexLayout.attributes)
			vertexSize += attribute.size();

		for (const VertexAttribute& attribute : vertexLayout.attributes) {

			GLenum glType = coreTypeToGLType(attribute.type);

			glVertexAttribPointer(index, attribute.count, glType, attribute.normalised, vertexSize, (void*)pointer);
			glEnableVertexAttribArray(index);

			pointer += attribute.size();
			index++;
		}

	}

	GLVertexBuffer::~GLVertexBuffer() {
		glDeleteBuffers(1, &id);
	}

	GLenum GLVertexBuffer::coreTypeToGLType(const VertexAttribute::Type& type) {
		
		switch (type) {
			case VertexAttribute::Type::Float:
				return GL_FLOAT;

			case VertexAttribute::Type::Float2:
				return GL_FLOAT;

			case VertexAttribute::Type::Float3:
				return GL_FLOAT;

			case VertexAttribute::Type::Float4:
				return GL_FLOAT;
		}
	}




	GLIndexBuffer::GLIndexBuffer() {
		glGenBuffers(1, &id);
	}

	void GLIndexBuffer::bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void GLIndexBuffer::unBind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void GLIndexBuffer::setData(const uint32_t& size, const void* data, uint32_t usage) {
		bind();
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	}

	GLIndexBuffer::~GLIndexBuffer() {
		glDeleteBuffers(1, &id);
	}

}