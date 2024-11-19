project "yaml"
	kind "StaticLib"
	language "C++"
    cppdialect "C++20"

	files
	{
		"yaml/src/**.h",
		"yaml/src/**.cpp",
		
		"yaml/include/**.h"
	}

	includedirs
	{
		"yaml/include"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
        targetdir "../build/Debug/lib"
        objdir  "../build/Debug/obj/yaml"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
        targetdir "../build/Debug/lib"
        objdir  "../build/Debug/obj/yaml"