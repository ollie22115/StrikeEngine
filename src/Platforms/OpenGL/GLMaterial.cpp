#include "StrikePCH.h"
#include "GLMaterial.h"
#include "Rendering/Renderer.h"
#include "glad/glad.h"

namespace Strike {

	void GLMaterial::uploadMat4(const std::string& uniformName, const glm::mat4& matrix){
		shaderPtr->setUniformMat4f(uniformName, matrix, GL_FALSE);	//TODO!!! check may need to be GL_TRUE
	}

	void GLMaterial::bind(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
		shaderPtr->bind();
		uploadMat4("v_viewMatrix", viewMatrix);
		uploadMat4("v_projectionMatrix", projectionMatrix);

		texturePtr->bind();
	}

}
