#pragma once

#include "BreakPoint.h"
#include "Log.h"

#ifdef STRIKE_DEBUG
#define STRIKE_ASSERT(x, platform, msg) if(!(x)){ Log::logError(platform, msg, __LINE__, __FILE__); STRIKE_SET_BREAKPOINT(); }	//TODO change so it causes a breakpoint instead
#define STRIKE_ERROR(x, platform, msg) if(!(x)) Log::logError(platform, msg, __LINE__, __FILE__)
#define STRIKE_WARNING(x, platform, msg) if(!(x)) Log::logWarning(platform, msg, __LINE__, __FILE__)
#else
#define STRIKE_ASSERT(x, platform, msg)
#define STRIKE_ERROR(x, platform, msg)
#define STRIKE_WARNING(x, platform, msg)
#endif

#ifdef STRIKE_DEBUG
#if defined(STRIKE_OPENGL) && defined(STRIKE_DIRECTX)
STRIKE_ASSERT(false, LOG_PLATFORM_CORE,  "Cannot have more Than one Rendering API's active at once!");
#endif
#endif