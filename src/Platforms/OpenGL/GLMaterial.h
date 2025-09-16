#pragma once

#include "GLShader.h"
#include "GLTexture.h"
#include "GLProgram.h"
#include "Resource/ResourceHandle.h"

namespace Strike {

	class GLMaterial{
	public:
		GLMaterial(const ResourceHandle&/*ResourcePointer&*/ shaderHandle, const ResourceHandle&/*ResourcePointer&*/ textureHandle) : 
			shaderHandle(shaderHandle), textureHandle(textureHandle) {}

		inline ResourceHandle/*ResourcePointer*/ getShaderHandle(){ return shaderHandle; }
		inline ResourceHandle/*ResourcePointer*/ getShaderHandle() const { return shaderHandle; }

		inline ResourceHandle/*ResourcePointer*/ getTextureHandle(){ return textureHandle; }
		inline ResourceHandle/*ResourcePointer*/ getTextureHandle() const { return textureHandle; }

		void uploadMat4(const std::string& uniformName, const glm::mat4& matrix);

		void bind(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

	private:
		ResourceHandle/*ResourcePointer*/ shaderHandle;
		ResourceHandle/*ResourcePointer*/ textureHandle;
	};

}