#include "StrikePCH.h"
#include "Camera.h"
#include "Utils/TransformMaths.h"

namespace Strike {

    glm::mat4 Camera::getViewMatrix(Transform& transform) {
        //TODO!!! For now only works for translations, extend to work for zoom (scale) and rotations

        glm::mat4 viewMatrix = TransformMaths::genIdentityMatrix();
        glm::vec3 translations = TransformMaths::getTranslations(transform);
        TransformMaths::translate(viewMatrix, -translations.x, -translations.y, -translations.z);

        return viewMatrix;
    }

    glm::mat4 Camera::getProjectionMatrix(const Camera& camera) {
        glm::mat4 projMatrix = glm::mat4(1.0f);
        TransformMaths::scale(projMatrix, 2.0f / camera.viewWidth, 2.0f / camera.viewHeight);

        return projMatrix;
    }

}

