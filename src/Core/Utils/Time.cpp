#include "StrikePCH.h"
#include "Time.h"

namespace Strike {

	int64_t currentTimeMS() {
		auto time = std::chrono::system_clock::now();
		auto duration = time.time_since_epoch();

		return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	}

}