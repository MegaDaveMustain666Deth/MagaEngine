require "vendor/premake-ninja/ninja"

workspace "Mega Engine"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "build"
    toolset "Clang"
    include "vendor/glad/glad.lua"

project "MegaEngine"
    language "C++"
    cppdialect "C++20"

    files
    {
        "src/*.cpp"
    } 

    includedirs
    {
        "src",
        "usr/include/GLFW",
        "vendor/glad/include",
        "vendor/json/include"
    }

    links
    {
        "glfw", "glad"
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    filter "configurations:Debug"
        kind "ConsoleApp"
        symbols "On"
        runtime "Debug"
        targetdir "build/Debug/build/bin"
        objdir  "build/Debug/obj"
        postbuildcommands "{COPYDIR} ../res Debug/build"

    filter "configurations:Release"
        kind "WindowedApp"
        runtime "Release"
        targetdir "build/Release/build/bin"
        objdir  "build/Release/obj"
        postbuildcommands "{COPYDIR} ../res Release/build"