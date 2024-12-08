#pragma once
#include <Platform/Platform.h>

// Standard libraries
#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <wrl.h> // ComPtr

#ifdef RUTAN_WINDOWS
	#define VC_EXTRALEAN
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>

	#define GLFW_INCLUDE_NONE
	#define GLFW_EXPOSE_NATIVE_WIN32

	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
#endif

// Math
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// Good to get access to in engine
#include <Core/Types.h>
#include <Utils/Logger.h>
