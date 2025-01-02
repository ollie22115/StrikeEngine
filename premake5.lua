project "StrikeEngine"
    kind "StaticLib"
    language "C++"

    targetdir("bin/" .. OutputDir)
    objdir("bin-int/" .. OutputDir)

    includedirs {
        "Dependencies/Vendor/glfw/include",         
        "Dependencies/Vendor/glad/include",
        "Dependencies/GLP",
        "Dependencies/Vendor/stbImage",
        "Dependencies/Vendor/glm"
    }

    files {"**.cpp", "**.h"}

    filter { "configurations:Debug" }
        defines { "STRIKE_DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "STRIKE_RELEASE" }
        optimize "On"