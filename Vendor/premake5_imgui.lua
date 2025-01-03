project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir("imgui/lib/%{prj.name}")
	objdir("imgui/lib/%{prj.name}")

	includedirs
	{
		"imgui",
		"glfw/include"
	}
	
	files
	{
		"imgui/imconfig.h",
		"imgui/imgui.h",
		"imgui/imgui.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_internal.h",
		"imgui/imgui_tables.cpp",
		"imgui/imgui_widgets.cpp",
		"imgui/imstb_rectpack.h",
		"imgui/imstb_textedit.h",
		"imgui/imstb_truetype.h",
		"imgui/imgui_demo.cpp",
		-- Backends
		"imgui/backends/imgui_impl_glfw.cpp",
		"imgui/backends/imgui_impl_dx11.cpp"
	}
		
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
	
	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"	
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
		
	-- Cleaning files specific for this project
	if _ACTION == 'clean' then
		print("ImGui: Cleaning up library files")
		os.rmdir("imgui/lib")
	end	