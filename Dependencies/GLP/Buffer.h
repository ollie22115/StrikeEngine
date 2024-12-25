#pragma once
#include <glad/glad.h>
#include <vector>

class Buffer {
public:
	Buffer(const GLenum target);

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

	VertexBuffer() : Buffer(GL_ARRAY_BUFFER), size(0) {};

	void pushAttribute(GLenum type, GLenum normalised, unsigned int count);
	void initAttributes();	
private:
	struct VertexAttribute {
		GLenum type;
		GLenum normalised;
		unsigned int count;

		VertexAttribute(GLenum type, GLenum normalised, unsigned int count) : type(type), normalised(normalised), count(count) {};
		int getSize();
	};

	unsigned int size;
	std::vector<VertexAttribute> attributes;
};




class IndexBuffer : public Buffer {
public:
	IndexBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {};
};

template<typename T>
inline void Buffer::setData(T* data, unsigned int count, GLenum usage){
	glBufferData(target, sizeof(T) * count, data, usage);
}
