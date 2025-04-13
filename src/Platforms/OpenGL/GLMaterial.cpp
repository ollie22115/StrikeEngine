#include "StrikePCH.h"
#include "GLMaterial.h"

namespace Strike {
	void GLMaterial::bind() {
		shader->bind();

		texture->bind();
	}

	bool GLMaterial::operator==(const GLMaterial& other) const {
		return this->shader->getID() == other.shader->getID() && this->texture->getId() == other.texture->getId();
	}

}
