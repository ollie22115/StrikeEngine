#pragma once

#include "Transform.h"

namespace Strike {

	struct CoreObjectData {
		CoreObjectData() = default;
		CoreObjectData(const bool& isVisible, const bool& isStatic) : isVisible(isVisible), isStatic(isStatic) {}
		CoreObjectData(const CoreObjectData& other) = default;

		bool isVisible = true;
		const bool isStatic = false;
	};

}