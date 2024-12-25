#include <iostream>

#include "Scene.h"

void Scene::addObject(Object& obj, float minX, float minY, float maxX, float maxY, float resX, float resY){
	//TODO!!! TEST IT'S PROBABLY BUGGY

#ifdef STRIKE_DEBUG == 1
	for (Object& object : objects) if (object.id == obj.id)
		std::cout << "ERROR: id of object already exists in objects\n";
#endif

	//centering object in place
	if (obj.minPosX() + obj.maxPosX() != 0) {
		float lengthX = obj.maxPosX() - obj.minPosX();
		float adjustmentX = (lengthX / 2) - obj.maxPosX();

		for (Triangle& tri : obj.triangles) for (Vertex& vert : tri.vertices)
			vert.pos.x() += adjustmentX;
	}
	if (obj.minPosY() + obj.maxPosY() != 0) {
		float lengthY = obj.maxPosY() - obj.minPosY();
		float adjustmentY = (lengthY / 2) - obj.maxPosY();

		for (Triangle& tri : obj.triangles) for (Vertex& vert : tri.vertices)
			vert.pos.y() += adjustmentY;
	}

	Mat4<float> transform = Mat4<float>::genIdentityMatrix();

	//translating object so it's min x and y position is at the origin 0
	transform.translate(obj.minPosX(), obj.minPosY());

	//scaling object so it fits the designated size on the screen
	float scaleX = (maxX - minX) / (obj.minPosX() - obj.maxPosX());
	float scaleY = (maxY - minY) / (obj.minPosY() - obj.maxPosY());
	transform.scale(scaleX, scaleY);
	
	//translating to position on the screen
	transform.translate(minX, minY);

	//transform to ndc coordinates
	transform.translate(-resX / 2, -resY / 2);
	transform.scale(1/(resX/2), 1/(resY/2));

	//applying transform to object
	obj.transform = transform;

	objects.push_back(obj);
}
