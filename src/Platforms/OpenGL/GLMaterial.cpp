#include "StrikePCH.h"
#include "GLMaterial.h"

namespace Strike {
	
	void GLMaterial::bind(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
		//TODO!!! make sure uniform variables names for both viewMatrix and projectionMatrix are correct
		shader->bind();
		uploadMat4("v_viewMatrix", viewMatrix);
		uploadMat4("v_projectionMatrix", projectionMatrix);

		texture->bind();
	}

	void GLMaterial::uploadMat4(const std::string& uniformName, const glm::mat4& matrix) {
		shader->setUniformMat4f(uniformName, matrix, GL_FALSE);	//TODO!!! check may need to be GL_TRUE
	}

	bool GLMaterial::operator==(const GLMaterial& other) const {
		return this->shader->getID() == other.shader->getID() && this->texture->getId() == other.texture->getId();
	}

}
