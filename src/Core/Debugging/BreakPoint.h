#if defined(_MSC_VER)      // MSVC
    #include <intrin.h>
    #define STRIKE_SET_BREAKPOINT() __debugbreak()

#elif defined(__GNUC__) || defined(__clang__)
    #include <signal.h>
    #define STRIKE_SET_BREAKPOINT() raise(SIGTRAP)

#else
    #include <cstdlib>
    #define STRIKE_SET_BREAKPOINT() std::abort()
#endif