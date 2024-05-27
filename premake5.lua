workspace "RutanEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"		--Final build with no logging
	}

startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- All the vendors/3d-parties files that we need
IncludeDir = {}
IncludeDir["spdlog"] 	= "Vendor/spdlog/include"
IncludeDir["stb"] 		= "Vendor/stb"
IncludeDir["entt"]		= "Vendor/entt/single_include"

LibraryDir = {}


project "Engine"
	location		"Engine"
	kind			"StaticLib"
	language		"C++"
	staticruntime	"on"
	systemversion	"latest"

	targetdir("Build/Bin/" .. outputdir .. "/%{prj.name}")
	objdir("Build/Bin-int/" .. outputdir .. "/%{prj.name}")

	-- Precompiled header files
	pchheader "EnginePCH.h"
	pchsource "%{prj.name}/Source/EnginePCH.cpp"
	
	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs 
	{
		"%{prj.name}",
		"%{prj.name}/Source",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.entt}"
	}
	
	libdirs 
	{ 
	}

	links
	{
	}

	filter "system:windows"
		cppdialect "C++20"

		defines
		{
			"RUTAN_BUILD_STATIC"
		}
		
		links
		{
			"d3d11"
		}

		postbuildcommands
		{
			-- If we are going to make the engine a DLL we can copy it to the sandbox on postbuild
			--("{COPY} %{cfg.buildtarget.relpath} ../Build/Bin" .. outputdir .. "/Sandbox")
		}

	filter "system:linux"
		cppdialect	"C++2a"
		pic			"On"

		defines
		{
			"RUTAN_BUILD_STATIC"
		}

	filter "configurations:Debug"
		defines "RUTAN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RUTAN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RUTAN_DIST"
		optimize "On"

project "Sandbox"
	location		"Sandbox"
	kind			"ConsoleApp"
	language		"C++"
	staticruntime	"on"
	systemversion	"latest"

	targetdir("Build/Bin/" .. outputdir .. "/%{prj.name}")
	objdir("Build/Bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs 
	{
		"Engine",
		"Engine/Source",
		"%{IncludeDir.spdlog}"
	}
	
	links
	{
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++20"

		defines
		{
		}

		postbuildcommands
		{
			-- If we are going to make the engine a DLL we can copy it to the sandbox on postbuild
			--("{COPY} %{cfg.buildtarget.relpath} ../Build/Bin" .. outputdir .. "/Sandbox")
		}

	filter "system:linux"
		cppdialect "C++2a"

		defines
		{
			"_X11"
		}
		
		links
		{
			"dl",
			"pthread"
		}

	filter "configurations:Debug"
		runtime "Debug"
		defines "RUTAN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		defines "RUTAN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		defines "RUTAN_DIST"
		optimize "On"
		
		
-- Cleaning up the project
newaction {
	trigger		= "clean",
	description = "Removing solutionfiles",
	execute     = function()
		print("Removing binaries and intermediate binaries")
		os.rmdir("Build/Bin")
		os.rmdir("Build/Bin-int")

		print("Removing Visual Studio files")
		os.rmdir(".vs")
		os.remove("**.sln")
		os.remove("**.vcxproj")
		os.remove("**.vcxproj.filters")
		os.remove("**.vcxproj.user")

		print("Removing makefiles")
		os.remove("**Makefile")

		print("Cleaning: Done")
	end
}