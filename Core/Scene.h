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
	inline Scene() = default;

	inline RenderableComponent& getRenderableComponent() { return renderableComponent; }
	inline const RenderableComponent& getRenderableComponent() const { return renderableComponent; }

	virtual void onStart() = 0;	//method that is called when a scene is being loaded
	virtual void onUpdate(const EventState& eventState, uint64_t timeStep) = 0;		//method that is called every frame upon every update call
	virtual void onFinish() = 0;	//method that is called when a scene is being unloaded

	~Scene() = default;

protected:
	RenderableComponent renderableComponent;
};