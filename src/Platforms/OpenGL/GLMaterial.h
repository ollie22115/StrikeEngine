#pragma once

#include "GLShader.h"
#include "GLTexture.h"
#include "GLProgram.h"
#include "Resource/ResourceHandle.h"

namespace Strike {

	class GLMaterial{
	public:
		GLMaterial(const ResourceHandle& shaderHandle, const ResourceHandle& textureHandle) : 
			shaderHandle(shaderHandle), textureHandle(textureHandle) {}

		inline ResourceHandle getShaderHandle(){ return shaderHandle; }
		inline ResourceHandle getTextureHandle(){ return textureHandle; }

		void uploadMat4(const std::string& uniformName, const glm::mat4& matrix);

		void bind(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

	private:
		ResourceHandle shaderHandle;
		ResourceHandle textureHandle;
	};

}