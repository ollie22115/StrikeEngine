OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

project "StrikeEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir("bin/" .. OutputDir)
    objdir("bin-int/" .. OutputDir)

    files {"**.cpp", "**.h", "**.c"}

    pchheader "StrikePCH.h"
    pchsource "src/Core/StrikePCH.cpp"

    removefiles {
        "Dependencies/Vendor/GLFW/**.c",
        "Dependencies/Vendor/glad/**.c"
    }

    includedirs {
        "Dependencies/Vendor/GLFW/glfw/include",       
        "Dependencies/Vendor/glad/include",
        "Dependencies/Vendor/stbImage",
        "Dependencies/Vendor/glm",
        "Dependencies/Vendor/entt/include",
        "src/Core",
        "src/Platforms"
    }

    filter { "configurations:Debug" }
        defines { "STRIKE_DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "STRIKE_RELEASE" }
        optimize "On"

    links{"GLFW", "Glad", "opengl32.lib"}

include "Dependencies/Vendor/GLFW/glfw/premake5.lua"

include "Dependencies/Vendor/glad/premake5.lua"