#include "StrikePCH.h"
#include <iostream>

#include "Scene.h"
#include "Debugging/StrikeDebug.h"

namespace Strike {
    
    Scene::Scene(const OnStartCallback& onStartCallback, const OnUpdateCallback& onUpdateCallback, const OnFinishCallback& onFinishCallback) :
        onStartCallback(onStartCallback), onUpdateCallback(onUpdateCallback), onFinishCallback(onFinishCallback) {}

    void Scene::onStart() {
        onStartCallback();
    }

    void Scene::onUpdate(const EventState& eventState, const uint64_t& deltaTime) {
        onUpdateCallback(eventState, deltaTime);
    }

    void Scene::onFinish() {
        onFinishCallback();
    }

    glm::mat4 Scene::getViewMatrix() {
        if(cameraObj != nullptr){
            STRIKE_ASSERT(cameraObj->hasComponent<EnttCamera>(), LOG_PLATFORM_CORE, 
                "No camera Component Attached to designated camera object in scene!");

            EnttCamera& camera = cameraObj->getComponent<EnttCamera>();
            return EnttCamera::getViewMatrix(cameraObj->getComponent<Transform>());

        } else
            STRIKE_ASSERT(false, LOG_PLATFORM_CORE, "No designated camera object in Scene!");
    }

    glm::mat4 Scene::getProjectionMatrix() {
        if(cameraObj != nullptr){
            STRIKE_ASSERT(cameraObj->hasComponent<EnttCamera>(), LOG_PLATFORM_CORE, 
                "No camera Component Attached to designated camera object in scene!");

            EnttCamera& camera = cameraObj->getComponent<EnttCamera>();

            return EnttCamera::getProjectionMatrix(camera);

        } else
            STRIKE_ASSERT(false, LOG_PLATFORM_CORE, "No designated camera object in scene!");
    }

    bool Scene::boxCast(const float& x0, const float& y0, const float& x1, const float& y1) {
        bool result = false;

        for (std::shared_ptr<Object>& object : objects) {
            std::shared_ptr<Bounds> bounds = object->getComponent<Bounds>();
            if (bounds != nullptr) 
                result = result || bounds->boxCast(object->transform, x0, y0, x1, y1);
        }

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

    void Scene::defaultOnStartCallback() {
        std::cout << "Scene Started!\n";
    }

    void Scene::defaultOnUpdateCallback(const EventState& eventState, const uint64_t& deltaTime) {
        std::cout << "Scene Updated!\n";
    }

    void Scene::defaultOnFinishCallback() {
        std::cout << "Scene Finished!\n";
    }


}