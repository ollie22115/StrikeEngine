#pragma once

#include <vector>
#include <array>
#include <string>
#include "../Dependencies/VectorsAndMatrices/Include/Vector.h"
#include "../Dependencies/VectorsAndMatrices/Include/Matrix.h"

//describes the position and texture coordinates of a vertex to be drawn
struct Vertex {
	//TODO!!!
	Vec4<float> pos;
	Vec2<float> texCoords;
};

//describes a drawable triangle made of Vertex vertices
struct Triangle {
	std::array<Vertex, 3> vertices;
};

//describes a collection of triangles and a texture that make up a object used in rendering
struct Object {
	std::string id;
	std::vector<Triangle> triangles;
	std::string textureName;
	bool visibility = true;
	Mat4<float> transform = Mat4<float>::genIdentityMatrix();

	//returns the x value of the vertex in the object thats the furthest along in the -x direction
	inline float minPosX() {
		float minPosX = triangles[0].vertices[0].pos.x();
		for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
			if (minPosX < vert.pos.x()) minPosX = vert.pos.x();
	}
	//returns the y value of the vertex in the object thats the furthest along in the -y direction
	float minPosY() {
		float minPosY = triangles[0].vertices[0].pos.y();
		for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
			if (minPosY < vert.pos.y()) minPosY = vert.pos.y();
	}
	//returns the x value of the vertex in the object thats the furthest along in the x direction
	float maxPosX() {
		float maxPosX = triangles[0].vertices[0].pos.x();
		for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
			if (maxPosX > vert.pos.x()) maxPosX = vert.pos.x();
	}
	//returns the y value of the vertex in the object thats the furthest along in the y direction
	float maxPosY() {
		float maxPosY = triangles[0].vertices[0].pos.y();
		for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
			if (maxPosY > vert.pos.y()) maxPosY = vert.pos.y();
	}
};

//describes a scene to be rendered
class Scene {
	//TODO!!!
public:
	void addObject(Object& obj, float minX, float minY, float maxX, float maxY, float resX, float resY);

private:
	std::vector<Object> objects;
	std::string vertexSourceFile;
	std::string fragSourceFile;
};