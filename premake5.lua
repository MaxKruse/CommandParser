workspace "CP"
	startproject "CP"

	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
	}

outputDir = "/%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}"

project "CP"
	location "CP"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	characterset "Unicode"
	vectorextensions "AVX"

	targetdir ("bin/%{prj.name}" .. outputDir)
	objdir ("bin/%{prj.name}/intermediates" .. outputDir)

	pchheader "pch.h"
	pchsource "CP/src/pch.cpp"

	files
	{
		"%{prj.name}/src/include/**.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src/include",
	}

	links
	{
		
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		optimize "Debug"
		symbols "Full"

	filter "configurations:Release"
		optimize "On"
		symbols "Off"

project "CommandParserExe"
	location "CommandParserExe"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	characterset "Unicode"
	vectorextensions "AVX"

	targetdir ("bin/%{prj.name}" .. outputDir)
	objdir ("bin/%{prj.name}/intermediates" .. outputDir)

	pchheader "pch.h"
	pchsource "CommandParserExe/src/pch.cpp"

	files
	{
		"%{prj.name}/src/include/**.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src/include",
		"CP/src/include/",
	}

	links
	{
		"CP"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		optimize "Debug"
		symbols "Full"

	filter "configurations:Release"
		optimize "On"
		symbols "Off"

project "CommandParserSingleHeaderUse"
	location "CommandParserSingleHeaderUse"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	characterset "Unicode"
	vectorextensions "AVX"

	targetdir ("bin/%{prj.name}" .. outputDir)
	objdir ("bin/%{prj.name}/intermediates" .. outputDir)

	pchheader "pch.h"
	pchsource "CommandParserSingleHeaderUse/src/pch.cpp"

	files
	{
		"%{prj.name}/src/include/**.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src/include",
	}

	links
	{
		
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		optimize "Debug"
		symbols "Full"

	filter "configurations:Release"
		optimize "On"
		symbols "Off"