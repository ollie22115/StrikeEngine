#pragma once
#include <glad/glad.h>
#include <vector>
#include "VertexLayout.h"

class Buffer {
public:
	inline Buffer(const GLenum target) : target(target), id(0) {};

	void init();

	inline GLuint getID() { return id; };
	inline GLuint getID() const { return id; };

	inline GLenum getTarget() { return target; }
	inline GLenum getTarget() const { return target; }

	template <typename T>
	void setData(T* data, unsigned int count, GLenum usage);
	
	void bind();

	~Buffer();

private:
	const GLenum target;
	GLuint id;
};

class VertexBuffer : public Buffer{

public:

	VertexBuffer() : Buffer(GL_ARRAY_BUFFER) {};

	void initAttributes(VertexLayout& vertexLayout);
};

class IndexBuffer : public Buffer {
public:
	IndexBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {};
};

template<typename T>
inline void Buffer::setData(T* data, unsigned int count, GLenum usage){
	glBufferData(target, sizeof(T) * count, data, usage);
}
