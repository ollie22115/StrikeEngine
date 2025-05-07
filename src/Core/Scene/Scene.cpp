#include "StrikePCH.h"
#include <iostream>

#include "Scene.h"
#include "Debugging/StrikeDebug.h"

namespace Strike {

    glm::mat4 Scene::getViewMatrix() {
        if (cameraObj != nullptr) {
            std::shared_ptr<Camera> camera = cameraObj->getComponent<Camera>();
            STRIKE_ASSERT(camera != nullptr, LOG_PLATFORM_CORE, "No camera Component Attached to designated camera object in scene!");

            return camera->getViewMatrix(cameraObj->transform);
        } else
            return Transform::genIdentityMatrix();
    }

    glm::mat4 Scene::getProjectionMatrix() {
        if (cameraObj != nullptr) {
            std::shared_ptr<Camera> camera = cameraObj->getComponent<Camera>();
            STRIKE_ASSERT(camera != nullptr, LOG_PLATFORM_CORE, "No camera Component Attached to designated camera object in scene!");

            return camera->getProjectionMatrix();

        } else
            return glm::mat4(1.0f);
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


}