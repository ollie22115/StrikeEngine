#pragma once

#include "RenderableComponent.h"
#include <string>
#include "StrikeTexture.h"

namespace Strike {

	RenderableObject genRec(const std::string& id, StrikeTexture& texture,
		float width, float height, float layer = 0.0f, glm::vec4 texCoords = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f), 
		glm::vec4 colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	RenderableObject genTriangle(const std::string& id, StrikeTexture& texture, 
		glm::vec3 p0, glm::vec3 p1, glm::vec3 p2,
		glm::vec2 texCoord0 = glm::vec2(0.0f, 0.0f), glm::vec2 texCoord1 = glm::vec2(0.0f, 0.0f), glm::vec2 texCoord2 = glm::vec2(0.0f, 0.0f),
		glm::vec4 colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	RenderableObject genCircle(float radius, glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f));
}