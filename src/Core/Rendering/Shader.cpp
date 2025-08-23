#include "Shader.h"

bool Strike::ShaderCore::operator==(const ShaderCore &other) const {
    return filePath == other.getFilePath();
}