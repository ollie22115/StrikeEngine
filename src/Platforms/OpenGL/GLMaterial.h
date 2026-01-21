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
		GLMaterial(const ResourcePointer<Shader>& shaderPtr, const ResourcePointer<Texture2D>& texturePtr, const glm::vec4& textureCoords) : 
			shaderPtr(shaderPtr), texturePtr(texturePtr), textureCoords(textureCoords) {}

		inline ResourcePointer<Shader> getShaderPtr(){ return shaderPtr; }
		inline ResourcePointer<Shader> getShaderPtr() const { return shaderPtr; }

		inline ResourcePointer<Texture2D> getTexturePtr(){ return texturePtr; }
		inline ResourcePointer<Texture2D> getTexturePtr() const { return texturePtr; }

		inline const glm::vec4& getTextureCoords() const { return textureCoords; };

		void uploadMat4(const std::string& uniformName, const glm::mat4& matrix);

		void bind(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

	private:
		ResourcePointer<Shader> shaderPtr;
		ResourcePointer<Texture2D> texturePtr;
		glm::vec4 textureCoords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	};

}