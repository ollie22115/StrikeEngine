#include "GLDebug.h"

namespace Strike {
	
	std::vector<float> getVertexBufferData(const GLVertexBuffer& vertexBuffer) {
		vertexBuffer.bind();

		float buffer[1024];
		std::vector<float> bufferData;
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, vertexBuffer.getSize(), &buffer[0]);
		for (int i = 0; i < vertexBuffer.getSize() / sizeof(float); i++)
			bufferData.push_back(buffer[i]);

		return bufferData;
	}

	std::vector<GLuint> getIndexBufferData(const GLIndexBuffer& indexBuffer) {
		indexBuffer.bind();

		GLuint buffer[1024];
		std::vector<GLuint> bufferData;
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexBuffer.getSize(), &buffer[0]);
		for (int i = 0; i < indexBuffer.getSize() / sizeof(GLuint); i++)
			bufferData.push_back(buffer[i]);

		return bufferData;
	}

	std::ostream& operator<<(std::ostream& os, const GLVertexBuffer& vertexBuffer) {
		os << "Vertex Buffer: " << vertexBuffer.getID() << ", (";

		std::vector<float> bufferData = getVertexBufferData(vertexBuffer);
		for (int i = 0; i < vertexBuffer.getSize() / sizeof(float); i++)
			os << bufferData[i] << ", ";
		os << ")";

		return os;
	}

	std::ostream& operator<<(std::ostream& os, const GLIndexBuffer& indexBuffer) {		
		os << "Index Buffer: " << indexBuffer.getID() << ", (";

		std::vector<GLuint> bufferData = getIndexBufferData(indexBuffer);
		for (int i = 0; i < indexBuffer.getSize() / sizeof(GLuint); i++)
			os << bufferData[i] << ", ";
		os << ")";

		return os;
	}

}
