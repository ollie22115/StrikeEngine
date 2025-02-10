#pragma once

#ifdef STRIKE_DEBUG
#define STRIKE_ASSERT(x, msg) if(!x) Log::logError(msg);
#else
#define STRIKE_ASSERT(x, msg)
#endif