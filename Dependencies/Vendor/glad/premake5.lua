project "Glad"
    kind "StaticLib"
    language "C"
    cppdialect "C++20"
    staticruntime "off"
    
    targetdir ("bin/{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}")
    objdir ("bin-int/{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"