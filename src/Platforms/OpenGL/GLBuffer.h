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

		void bind();
		void unBind();

		virtual void setData(const uint32_t& size, void* data, uint32_t usage);

		void setVertexLayout(const VertexLayout& vertexLayout);

		~GLVertexBuffer();

	private:
		static GLenum coreTypeToGLType(const VertexAttribute::Type& type);

		GLuint id;
	};

	class GLIndexBuffer {
	public:
		GLIndexBuffer();

		void bind();
		void unBind();

		void setData(const uint32_t& size, const void* data, uint32_t usage);

		~GLIndexBuffer();

	private:
		GLuint id;
	};

}