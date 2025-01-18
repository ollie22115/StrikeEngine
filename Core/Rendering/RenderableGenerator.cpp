#include "RenderableGenerator.h"

namespace Strike {

	RenderableObject genRec(const std::string& id, StrikeTexture& texture,
		float width, float height, float layer, glm::vec3 origin, glm::vec4 texCoords, glm::vec4 colour) {
		//TODO!!! Remember to include texture files and id
		RenderableObject rec;
		rec.id = id;
		rec.texture = &texture;

		Triangle t1;
		t1.vertices[0].pos = glm::vec4(-width + origin.x, -height + origin.y, layer, 0.0f);
		t1.vertices[1].pos = glm::vec4(width + origin.x, -height + origin.y, layer, 0.0f);
		t1.vertices[2].pos = glm::vec4(width + origin.x, height + origin.y, layer, 0.0f);

		t1.vertices[0].texCoords = glm::vec2(texCoords[0], texCoords[1]);
		t1.vertices[1].texCoords = glm::vec2(texCoords[2], texCoords[1]);
		t1.vertices[2].texCoords = glm::vec2(texCoords[2], texCoords[3]);

		t1.vertices[0].colour = colour;
		t1.vertices[1].colour = colour;
		t1.vertices[2].colour = colour;


		Triangle t2;
		t2.vertices[0].pos = glm::vec4(-width + origin.x, -height + origin.y, layer, 0.0f);
		t2.vertices[1].pos = glm::vec4(width + origin.x, height + origin.y, layer, 0.0f);
		t2.vertices[2].pos = glm::vec4(-width + origin.x, height + origin.y, layer, 0.0f);

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