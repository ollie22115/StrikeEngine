#pragma once
#include <iostream>
#include <vector>
#include "GLBuffer.h"

namespace Strike {

	std::vector<float> getVertexBufferData(const GLVertexBuffer& vertexBuffer);
	std::vector<GLuint> getIndexBufferData(const GLIndexBuffer& indexBuffer);

	std::ostream& operator<<(std::ostream& os, const GLVertexBuffer& vertexBuffer);
	std::ostream& operator<<(std::ostream& os, const GLIndexBuffer& indexBuffer);

}