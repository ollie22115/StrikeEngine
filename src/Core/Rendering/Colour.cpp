#include "StrikePCH.h"
#include "Colour.h"

glm::vec4 Strike::Colour::genColour(float r, float g, float b, float a) {
    return glm::vec4(r, g, b, a);
}

glm::vec4 Strike::Colour::red() {
    return glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

glm::vec4 Strike::Colour::green() {
    return glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
}

glm::vec4 Strike::Colour::blue() {
    return glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

glm::vec4 Strike::Colour::white() {
    return glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

glm::vec4 Strike::Colour::black() {
    return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
