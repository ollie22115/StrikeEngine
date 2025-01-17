#pragma once
#include <array>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <Buffer.h>

//describes the position and texture coordinates of a vertex to be drawn
struct Vertex {
	//TODO!!!
	glm::vec4 pos;
	glm::vec2 texCoords = glm::vec2(0.0f, 0.0f);
	glm::vec4 colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

//describes a drawable triangle made of Vertex vertices
struct Triangle {
	std::array<Vertex, 3> vertices;
};

struct Object {
	std::string id;
	std::vector<Triangle> triangles;
	std::string textureName;
	bool visibility = true;
	glm::mat4 transform = glm::mat4();

	//returns the x value of the vertex in the object thats the furthest along in the -x direction
	inline float minPosX() {
		float minPosX = triangles[0].vertices[0].pos.x;
		for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
			if (minPosX < vert.pos.x) minPosX = vert.pos.x;

		return minPosX;
	}
	//returns the y value of the vertex in the object thats the furthest along in the -y direction
	float minPosY() {
		float minPosY = triangles[0].vertices[0].pos.y;
		for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
			if (minPosY < vert.pos.y) minPosY = vert.pos.y;

		return minPosY;
	}
	//returns the x value of the vertex in the object thats the furthest along in the x direction
	float maxPosX() {
		float maxPosX = triangles[0].vertices[0].pos.x;
		for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
			if (maxPosX > vert.pos.x) maxPosX = vert.pos.x;

		return maxPosX;
	}
	//returns the y value of the vertex in the object thats the furthest along in the y direction
	float maxPosY() {
		float maxPosY = triangles[0].vertices[0].pos.y;
		for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
			if (maxPosY > vert.pos.y) maxPosY = vert.pos.y;

		return maxPosY;
	}
};

//describes a collection of triangles and a texture that make up a object used in rendering
struct RenderableComponent {
	std::vector<Object> objects;

	std::string vertexSourceFilePath = "";
	std::string fragSourceFilePath = "";

	VertexLayout vertexLayout;

	void addObject(Object& obj, float minX, float minY, float maxX, float maxY, 
		float resX, float resY, 
		bool doCenter = true, bool defaultVisibility = true);

	void configureBuffers(VertexBuffer& vb, IndexBuffer& ib);
};