#pragma once
#include <array>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "VertexLayout.h"

namespace GLP {
	
	template <typename T, uint32_t count>
	std::array<T, count> getBufferData(GLenum target, uint32_t& offset) {
		std::array<T, count> bufferData;

		glGetBufferSubData(GL_ARRAY_BUFFER, offset, count * sizeof(T), &bufferData[0]);
		return bufferData;
	}

}