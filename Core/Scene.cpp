#include <iostream>

#include "Scene.h"
#include "Debugging/Log.h"

void Scene::addObject(RenderableComponent& obj, float minX, float minY, float maxX, float maxY, float resX, float resY, bool doCenter){
	//TODO!!! TEST IT'S PROBABLY BUGGY

#ifdef STRIKE_DEBUG
	for (RenderableComponent& object : renderableObjects) if (object.id == obj.id)
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

	glm::mat4 transform(1.0f);

	//translating object so it's min x and y position is at the origin 0
	transform = glm::translate(transform, glm::vec3(obj.minPosX(), obj.minPosY(), 0.0f));

	//scaling object so it fits the designated size on the screen
	float scaleX = (maxX - minX) / (obj.minPosX() - obj.maxPosX());
	float scaleY = (maxY - minY) / (obj.minPosY() - obj.maxPosY());
	transform = glm::scale(transform, glm::vec3(scaleX, scaleY, 1.0f));

	//translating to position on the screen
	transform = glm::translate(transform, glm::vec3(minX, minY, 0.0f));

	//transform to ndc coordinates
	transform = glm::translate(transform, glm::vec3(-resX / 2, -resY / 2, 0.0f));
	transform = glm::scale(transform, glm::vec3(1 / (resX / 2), 1 / (resY / 2), 0.0f));

	//applying transform to object
	obj.transform = transform;

	renderableObjects.push_back(obj);
}