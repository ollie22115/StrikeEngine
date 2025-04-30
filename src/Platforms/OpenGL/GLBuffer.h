#pragma once
#include <glad/glad.h>
#include <vector>
#include <array>
#include "Rendering/Buffer.h"

namespace Strike {

	//TODO!!! Remove VertexBuffer dependency
	class GLVertexBuffer {
	public:
		GLVertexBuffer();

		inline GLuint getID() const { return id; }
		inline size_t getSize() const { return size; }

		void bind() const;
		void unBind() const;

		void setData(const size_t& size, void* data, uint32_t usage);

		void setVertexLayout(const VertexLayout& vertexLayout);

		~GLVertexBuffer();

	private:
		static GLenum coreTypeToGLType(const VertexAttribute::Type& type);

		GLuint id;
		size_t size;
	};

	class GLIndexBuffer {
	public:
		GLIndexBuffer();

		inline GLuint getID() const { return id; }
		inline size_t getSize() const { return size; }

		void bind() const;
		void unBind() const;

		void setData(const size_t& size, const void* data, uint32_t usage);

		~GLIndexBuffer();

	private:
		GLuint id;
		size_t size;
	};

}