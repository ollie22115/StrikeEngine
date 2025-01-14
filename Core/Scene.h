#pragma once

#include <vector>
#include <array>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "EventsAndInput/EventState.h"
#include "RenderableComponent.h"

//describes a scene to be rendered
class Scene {
	//TODO!!!
public:
	inline Scene(const std::string& vertexSourceFile, const std::string& fragSourceFile) : 
		vertexSourceFile(vertexSourceFile), fragSourceFile(fragSourceFile) {};

	void addObject(RenderableComponent& obj, float minX, float minY, float maxX, float maxY, float resX, float resY, bool doCenter = true);

	virtual void onStart() = 0;	//method that is called when a scene is being loaded
	virtual void onUpdate(const EventState& eventState) = 0;		//method that is called every frame upon every update call
	virtual void onFinish() = 0;	//method that is called when a scene is being unloaded

	~Scene() = default;

private:
	std::vector<RenderableComponent> renderableObjects;
	std::string vertexSourceFile;
	std::string fragSourceFile;
};