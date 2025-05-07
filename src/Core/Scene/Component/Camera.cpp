#include "StrikePCH.h"
#include "Camera.h"
#include "Utils/Transform.h"

namespace Strike {

    Camera::Camera(const float& viewWidth, const float& viewHeight) :
        Component(Component::Type::Camera), viewWidth(viewWidth), viewHeight(viewHeight) {

    }

    glm::mat4 Camera::getViewMatrix(const glm::mat4& transform) {
        glm::mat4 viewMatrix = Transform::genIdentityMatrix();
        glm::vec3 translations = Transform::getTranslations(transform);
        Transform::translate(viewMatrix, -translations.x, -translations.y, -translations.z);
        return viewMatrix;
    }

    glm::mat4 Camera::getProjectionMatrix() {
        glm::mat4 projMatrix = glm::mat4(1.0f);
        Transform::scale(projMatrix, 2.0f / viewWidth, 2.0f / viewHeight);

        return projMatrix;
    }

    bool Camera::isRenderable() {
        return false;
    }

}

