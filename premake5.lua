require "vendor/premake-ninja/ninja"

workspace "MegaEngine"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "build"
    toolset "Clang"
    include "vendor/glad/glad.lua"
    include "vendor/yaml.lua"

project "MegaEngine"
    language "C++"
    cppdialect "C++20"

    files
    {
        "src/**.cpp",
    } 

    includedirs
    {
        "src",
        "usr/include",
        "vendor/glad/include",
        "vendor/json/include",
        "vendor/yaml/include"   
    }

    links
    {
        "glfw", "glad", "yaml"
    }

    defines
    {
        "GLFW_INCLUDE_NONE"
    }

    filter "configurations:Debug"
        kind "ConsoleApp"
        symbols "On"
        runtime "Debug"
        targetdir "build/Debug/build"
        objdir  "build/Debug/obj"
        postbuildcommands "{COPYDIR} ../ExampleGame/res Debug/build"

    filter "configurations:Release"
        kind "WindowedApp"
        runtime "Release"
        optimize "On"
        targetdir "build/Release/build"
        objdir  "build/Release/obj"
        postbuildcommands "{COPYDIR} ../ExampleGame/res Release/build"