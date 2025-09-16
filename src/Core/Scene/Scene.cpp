#include "StrikePCH.h"
#include <iostream>

#include "Scene.h"
#include "Debugging/StrikeDebug.h"
#include "Component/Bounds.h"
#include "Component/Camera.h"
#include "Rendering/Renderer.h"

namespace Strike {

    std::shared_ptr<Object> Scene::createObject(const bool& isStatic) {
        objects.push_back(std::make_shared<Object>(registry, true, isStatic));
        return objects[objects.size() - 1];
    }

    void Scene::load(std::unique_ptr<Renderer>& renderer) {
        onStart();

        for (std::shared_ptr<Object>& object : objects)
            renderer->loadObject(object);
    }

    void Scene::onStart() {
        std::cout << "Scene Started!\n";
    }

    void Scene::onUpdate(const EventState& eventState, const uint64_t& deltaTime) {
       std::cout << "Scene Updated!\n";
    }

    void Scene::onFinish() {
        std::cout << "Scene Started!\n";
    }

    glm::mat4 Scene::getViewMatrix() {
        if(cameraObj != nullptr){
            STRIKE_ASSERT(cameraObj->hasComponent<Camera>(), LOG_PLATFORM_CORE, 
                "No camera Component Attached to designated camera object in scene!");

            Camera& camera = cameraObj->getComponent<Camera>();
            return Camera::getViewMatrix(cameraObj->getComponent<Transform>());

        } else
            STRIKE_ASSERT(false, LOG_PLATFORM_CORE, "No designated camera object in Scene!");
    }

    glm::mat4 Scene::getProjectionMatrix() {
        if(cameraObj != nullptr){
            STRIKE_ASSERT(cameraObj->hasComponent<Camera>(), LOG_PLATFORM_CORE, 
                "No camera Component Attached to designated camera object in scene!");

            Camera& camera = cameraObj->getComponent<Camera>();

            return Camera::getProjectionMatrix(camera);

        } else
            STRIKE_ASSERT(false, LOG_PLATFORM_CORE, "No designated camera object in scene!");
    }

    bool Scene::boxCast(const float& x0, const float& y0, const float& x1, const float& y1) {
        
        bool result = false;

        auto view = registry.view<Transform, BoxBounds>();
        view.each([&](auto entity, Transform& transform, BoxBounds& bounds) {
            result = result || BoxBounds::boxCast(bounds, transform, x0, y0, x1, y1);
        });

        auto view2 = registry.view<Transform, RadiusBounds>();
        view2.each([&](auto entity, Transform& transform, RadiusBounds& bounds) {
            result = result || RadiusBounds::boxCast(bounds, transform, x0, y0, x1, y1);
        });

        return result;
    }

    bool Scene::rayCast(const float& oX, const float& oY, const float& dX, const float& dY) {
        //TODO!!!
        return false;
    }

    bool Scene::rayCast(const float& oX, const float& oY, const float& dX, const float& dY, const float& maxDistance) {
        //TODO!!!
        return false;
    }

}