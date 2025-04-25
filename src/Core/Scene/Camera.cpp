#include "Camera.h"

#include "Utils/Transform.h"

namespace Strike {

    glm::mat4 TopDownCamera::getViewMatrix() {
        return transform;
    }

    glm::mat4 TopDownCamera::getProjectionMatrix() {
        //TODO!!! TEST

        glm::mat4 projMatrix = glm::mat4(1.0f);
        Transform::scale(projMatrix, 2.0f / viewWidth, 2.0f / viewHeight);
        Transform::translate(projMatrix, -1.0f, -1.0f);

        return projMatrix;
    }

}
