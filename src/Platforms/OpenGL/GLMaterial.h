#pragma once

#include "GLShader.h"
#include "GLTexture.h"
#include "GLProgram.h"
#include "Resource/ResourceHandle.h"
#include "Resource/ResourceManager.h"

namespace Strike {

	class GLMaterial{
	public:
		GLMaterial(const ResourcePointer<Shader>& shaderPtr, const ResourcePointer<Texture2D>& texturePtr) : 
			shaderPtr(shaderPtr), texturePtr(texturePtr) {}

		inline ResourcePointer<Shader> getShaderPtr(){ return shaderPtr; }
		inline ResourcePointer<Shader> getShaderPtr() const { return shaderPtr; }

		inline ResourcePointer<Texture2D> getTexturePtr(){ return texturePtr; }
		inline ResourcePointer<Texture2D> getTexturePtr() const { return texturePtr; }

		void uploadMat4(const std::string& uniformName, const glm::mat4& matrix);

		void bind(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

	private:
		ResourcePointer<Shader> shaderPtr;
		ResourcePointer<Texture2D> texturePtr;
	};

}