require "premake-ninja/ninja"

project "imgui"

	kind "StaticLib"
	language "C"
	staticruntime "on"

	files
	{
        "vendor/imgui/backends/imgui_impl_opengl3.cpp",
        "vendor/imgui/backends/imgui_impl_glfw.cpp",
        "imgui/backends/imgui*.cpp"
	}

    includedirs
    {
        "vendor/imgui/backends", 
        "vendor/imgui"
    }

	filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        targetdir "../build/Debug/bin"
        objdir  "../build/Debug/obj"

	filter "configurations:Release"
        runtime "Release"
        targetdir "../build/Release/bin"
        objdir  "../build/Release/obj"