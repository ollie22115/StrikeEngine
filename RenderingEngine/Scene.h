#pragma once

#include <vector>
#include <array>
#include <stirng>

//describes a the position and texture coordinates of a vertex to be drawn
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
	vector<Mat4<float>> transforms;

	//returns the x value of the vertex in the object thats the furthest along in the -x direction
	float minPosX();
	//returns the y value of the vertex in the object thats the furthest along in the -y direction
	float minPosY();
	//returns the x value of the vertex in the object thats the furthest along in the x direction
	float maxPosX();
	//returns the y value of the vertex in the object thats the furthest along in the y direction
	float maxPosY();
};

//describes a scene to be rendered
class Scene {
	//TODO!!!
public:
	void addObject(Object& obj);
	void placeObject(const std::string& id, float minX, float minY, float maxX, float maxY);

private:
	std::vector<Object> objects;
	std::string vertexSourceFile;
	std::string fragSourceFile;
};