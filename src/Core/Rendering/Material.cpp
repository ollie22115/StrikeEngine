#include "StrikePCH.h"
#include "Material.h"

namespace Strike {

    bool Material::operator==(const Material& other) const {
        return this->shaderPath == other.shaderPath && this->texturePath == other.texturePath;
    }

}
