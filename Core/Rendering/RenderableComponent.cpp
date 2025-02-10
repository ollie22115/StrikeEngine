#include "RenderableComponent.h"
#include "../Debugging/Log.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Strike {

	void RenderableComponent::addObject(RenderableObject& obj, float minX, float minY, float maxX, float maxY, 
		float resX, float resY, float rotation, bool doCenter, bool defaultVisibility) {
		//TODO!!! TEST IT'S PROBABLY BUGGY

		obj.visibility = defaultVisibility;

#ifdef STRIKE_DEBUG
		for (RenderableObject& object : objects) if (object.id == obj.id)
			Log::logError("error id: " + object.id + "already exists!");
#endif

		//centering object in place
		if (doCenter) {
			if (obj.minPosX() + obj.maxPosX() != 0) {
				float lengthX = obj.maxPosX() - obj.minPosX();
				float adjustmentX = (lengthX / 2) - obj.maxPosX();

				for (Triangle& tri : obj.triangles) for (Vertex& vert : tri.vertices)
					vert.pos.x += adjustmentX;
			}
			if (obj.minPosY() + obj.maxPosY() != 0) {
				float lengthY = obj.maxPosY() - obj.minPosY();
				float adjustmentY = (lengthY / 2) - obj.maxPosY();

				for (Triangle& tri : obj.triangles) for (Vertex& vert : tri.vertices)
					vert.pos.y += adjustmentY;
			}
		}

		//Generating Transform
		glm::mat4 transform(1.0f);

		//scaling object so it fits the designated size on the screen
		float scaleX = (maxX - minX) / (obj.width());
		float scaleY = (maxY - minY) / (obj.height());
		transform = glm::scale(transform, glm::vec3(scaleX, scaleY, 1.0f));

		//applying rotation to object
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * transform;

		//translating object so it's min x and y position is at the origin 0
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(-obj.minPosX() * scaleX, -obj.minPosY() * scaleY, 0.0f)) * transform;

		//translating to position on the screen
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(minX, minY, 0.0f)) * transform;

		//transform to ndc coordinates
		transform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / (resX / 2.0f), 1.0f / (resY / 2.0f), 1.0f)) * transform;
		transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, 0.0f)) * transform;

		//applying transform to object
		obj.transform = glm::transpose(transform);

		objects.push_back(obj);
	}

	void RenderableComponent::configureBuffers(GLP::VertexBuffer& vb, GLP::IndexBuffer& ib) {
		vb.bind();
		ib.bind();

		vb.initAttributes(vertexLayout);
	}

	bool Vertex::operator==(const Vertex& other) {
		if (this->pos != other.pos) return false;
		else if (this->texCoords != other.texCoords) return false;
		else return true;
	}

}