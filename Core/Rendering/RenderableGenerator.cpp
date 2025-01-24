#include "RenderableGenerator.h"

namespace Strike {

	RenderableObject genRec(const std::string& id, StrikeTexture& texture,
		float width, float height, float layer, glm::vec4 texCoords, glm::vec4 colour) {
		//TODO!!! Check over especially texture coordinates

		RenderableObject rec;
		rec.id = id;
		rec.texture = &texture;

		Triangle t1;
		t1.vertices[0].pos = glm::vec4(-(width/2), (- height/2), layer, 1.0f);
		t1.vertices[1].pos = glm::vec4((width/2), (-height/2), layer, 1.0f);
		t1.vertices[2].pos = glm::vec4((width/2), (height/2), layer, 1.0f);

		t1.vertices[0].texCoords = glm::vec2(texCoords[0], texCoords[1]);
		t1.vertices[1].texCoords = glm::vec2(texCoords[2], texCoords[1]);
		t1.vertices[2].texCoords = glm::vec2(texCoords[2], texCoords[3]);

		t1.vertices[0].colour = colour;
		t1.vertices[1].colour = colour;
		t1.vertices[2].colour = colour;


		Triangle t2;
		t2.vertices[0].pos = glm::vec4((-width/2), (-height/2), layer, 1.0f);
		t2.vertices[1].pos = glm::vec4((width/2), (height/2), layer, 1.0f);
		t2.vertices[2].pos = glm::vec4((-width/2), (height/2), layer, 1.0f);

		t2.vertices[0].texCoords = glm::vec2(texCoords[0], texCoords[1]);
		t2.vertices[1].texCoords = glm::vec2(texCoords[2], texCoords[3]);
		t2.vertices[2].texCoords = glm::vec2(texCoords[0], texCoords[3]);

		t2.vertices[0].colour = colour;
		t2.vertices[1].colour = colour;
		t2.vertices[2].colour = colour;

		rec.triangles.push_back(t1);
		rec.triangles.push_back(t2);

		return rec;
	}

	RenderableObject genTriangle(const std::string& id, StrikeTexture& texture, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2,
		glm::vec2 texCoord0, glm::vec2 texCoord1, glm::vec2 texCoord2, glm::vec4 colour) {
		
		RenderableObject triangle;
		triangle.id = id;
		triangle.texture = &texture;
		
		Triangle t;
		t.vertices[0].pos = glm::vec4(p0.x, p0.y, p0.z, 1.0f);
		t.vertices[0].texCoords = texCoord0;
		t.vertices[0].colour = colour;

		t.vertices[1].pos = glm::vec4(p1.x, p1.y, p1.z, 1.0f);
		t.vertices[1].texCoords = texCoord1;
		t.vertices[1].colour = colour;

		t.vertices[2].pos = glm::vec4(p2.x, p2.y, p2.z, 1.0f);
		t.vertices[2].texCoords = texCoord2;
		t.vertices[2].colour = colour;

		triangle.triangles.push_back(t);

		return triangle;
	}

	RenderableObject genTriangle(float p0, float p1, float p2, glm::vec3 origin) {
		//TODO!!!

		RenderableObject triangle;
		return triangle;
	}

	RenderableObject genCircle(float radius, glm::vec3 origin) {
		//TODO!!!

		RenderableObject circle;
		return circle;
	}

}