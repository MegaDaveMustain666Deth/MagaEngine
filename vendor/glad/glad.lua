require "../premake-ninja/ninja"

project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	files
	{
        "src/glad.c"
	}

    includedirs
    {
        "include"
    }

    links
    {
        "GL"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        targetdir "../../build/Debug/lib"
        objdir  "../../build/Debug/obj/glad"

    filter "configurations:Release"
        runtime "Release"
        targetdir "../../build/Release/lib"
        objdir  "../../build/Release/obj/glad"