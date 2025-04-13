#pragma once
#include "Rendering/Material.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLProgram.h"

namespace Strike {

	class GLMaterial {
	public:
		GLMaterial(std::shared_ptr<GLProgram>& shader, std::shared_ptr<GLTexture2D>& texture) : shader(shader), texture(texture) {}

		inline std::shared_ptr<GLProgram>& getShader() { return shader; }
		inline std::shared_ptr<GLTexture2D>& getTexture() { return texture; }

		void bind();

		bool operator ==(const GLMaterial& other) const;

	private:
		std::shared_ptr<GLProgram> shader;

		std::shared_ptr<GLTexture2D> texture; //for now only supports one 2D texture
	};

}