#pragma once
#include <Platform/Platform.h>

#ifdef RUTAN_WINDOWS
	#define VC_EXTRALEAN
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>

	#define GLFW_INCLUDE_NONE
	#define GLFW_EXPOSE_NATIVE_WIN32
#endif

// Standard libraries
#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

// Good to get access to in engine
#include <Core/Types.h>
#include <Utils/Logger.h>

// Graphics
#ifdef RUTAN_D3D11
	#include <d3d11.h>
	#include <dxgi1_3.h>
	#include <wrl.h> 	// ComPtr
	#pragma comment(lib, "d3d11.lib")
	#pragma comment(lib, "dxgi.lib")

	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
#endif
