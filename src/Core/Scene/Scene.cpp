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

}