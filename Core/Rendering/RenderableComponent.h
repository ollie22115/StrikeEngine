#pragma once
#include <array>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <Buffer.h>
#include "StrikeTexture.h"


namespace Strike {

	//describes the position and texture coordinates of a vertex to be drawn
	struct Vertex {
		//TODO!!!
		glm::vec4 pos;
		glm::vec2 texCoords = glm::vec2(0.0f, 0.0f);

		Vertex() = default;
		inline Vertex(const glm::vec4& pos, const glm::vec2& texCoords, const glm::vec4& colour) :
			pos(pos), texCoords(texCoords) {
		};

		inline static uint32_t count() { return 6; }

		bool operator ==(const Vertex& other);
	};

	//describes a drawable triangle made of Vertex vertices
	struct Triangle {
		std::array<Vertex, 3> vertices;
	};

	struct RenderableObject {
		std::string id;
		std::vector<Triangle> triangles;
		StrikeTexture* texture;
		bool visibility = true;
		glm::vec4 colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::mat4 transform = glm::mat4();

		//returns the x value of the vertex in the object thats the furthest along in the -x direction
		float minPosX() {
			float minPosX = triangles[0].vertices[0].pos.x;
			for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
				if (minPosX > vert.pos.x) minPosX = vert.pos.x;

			return minPosX;
		}
		//returns the y value of the vertex in the object thats the furthest along in the -y direction
		float minPosY() {
			float minPosY = triangles[0].vertices[0].pos.y;
			for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
				if (minPosY > vert.pos.y) minPosY = vert.pos.y;

			return minPosY;
		}
		//returns the x value of the vertex in the object thats the furthest along in the x direction
		float maxPosX() {
			float maxPosX = triangles[0].vertices[0].pos.x;
			for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
				if (maxPosX < vert.pos.x) maxPosX = vert.pos.x;

			return maxPosX;
		}
		//returns the y value of the vertex in the object thats the furthest along in the y direction
		float maxPosY() {
			float maxPosY = triangles[0].vertices[0].pos.y;
			for (const Triangle& tri : triangles) for (const Vertex& vert : tri.vertices)
				if (maxPosY < vert.pos.y) maxPosY = vert.pos.y;

			return maxPosY;
		}

		float width() {
			return maxPosX() - minPosX();
		}

		float height() {
			return maxPosY() - minPosY();
		}
	};

	//describes a collection of triangles and a texture that make up a object used in rendering
	struct RenderableComponent {
		std::vector<RenderableObject> objects;

		std::vector<StrikeTexture> textures;

		std::string vertexSourceFilePath = "";
		std::string fragSourceFilePath = "";

		GLP::VertexLayout vertexLayout;

		void addObject(RenderableObject& obj, float minX, float minY, float maxX, float maxY,
			float resX, float resY,
			bool doCenter = true, bool defaultVisibility = true);

		void configureBuffers(GLP::VertexBuffer& vb, GLP::IndexBuffer& ib);
	};

}