#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Strike {
    
    glm::mat4 Transform::genIdentityMatrix() {
        return glm::mat4(1.0f);
    }

    glm::mat4 Transform::genScaleMatrix(const float& x, const float& y, const float& z) {
        return glm::scale(genIdentityMatrix(), glm::vec3(x, y, z));
    }

    glm::mat4 Transform::genTranslationMatrix(const float& x, const float& y, const float& z) {
        return glm::translate(genIdentityMatrix(), glm::vec3(x, y, z));
    }

    glm::mat4 Transform::genRotationMatrix(const float& angle, const glm::vec3& axis) {
        return glm::rotate(genIdentityMatrix(), angle, axis);
    }



    void Transform::scale(glm::mat4& matrix, const float& x, const float& y, const float& z) {
        matrix = genScaleMatrix(x, y, z) * matrix;
    }

    void Transform::translate(glm::mat4& matrix, const float& x, const float& y, const float& z) {
        matrix = genTranslationMatrix(x, y, z) * matrix;
    }

    void Transform::rotate(glm::mat4& matrix, const float& angle, const glm::vec3& axis) {
        matrix = genRotationMatrix(angle, axis) * matrix;
    }

    glm::vec3 Transform::getTranslations(const glm::mat4& matrix) {
        return glm::vec3(matrix[3][0], matrix[3][1], matrix[3][2]);
    }

    glm::vec3 Transform::getScales(const glm::mat4& matrix) {
        return glm::vec3(matrix[0][0], matrix[1][1], matrix[2][2]);
    }

}
