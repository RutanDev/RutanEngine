#pragma once

// Standard libraries
#include <iostream>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>


// Good to have everywhere
#include <Platform/Platform.h>
#include <Core/Types.h>

#ifdef RUTAN_D3D11
	#include <d3d11.h>
	#include <dxgi1_3.h>
	#include <wrl.h> 	// ComPtr

	#pragma comment(lib, "d3d11.lib")
	#pragma comment(lib, "dxgi.lib")


	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
#endif


// Singletons
#include <Utils/Logger.h>
