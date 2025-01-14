#pragma once

#include "RenderableComponent.h"
#include <string>

RenderableComponent genRec(const std::string& id, const std::string textureFile, 
	float width, float height, float layer = 0.0f, glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec4 texCoords = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f), glm::vec4 colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

RenderableComponent& genTriangle(float p0, float p1, float p2, glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f));

RenderableComponent& genCircle(float radius, glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f));