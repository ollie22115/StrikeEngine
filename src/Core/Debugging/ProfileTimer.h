#pragma once
#include <string>
#include <iostream>

#include "Utils/Time.h"

namespace Strike {

	class ProfileTimer {
	public:
		inline ProfileTimer(const std::string& name) : name(name) {
			start = currentTimeMS();
		}

		inline ~ProfileTimer() {
			std::cout << name << ":" << (currentTimeMS() - start) << "\n";
		}

	private:
		std::string name;
		uint64_t start;
	};

}
