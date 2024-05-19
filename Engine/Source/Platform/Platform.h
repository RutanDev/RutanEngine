#pragma once

/*
	Checking which platform we are on
*/ 
#ifdef _WIN32
	#ifdef _WIN64
		#define RUTAN_WINDOWS
	#else
		#error "Who uses 32-bit systems anymore???"
	#endif

#elif defined(__unix__) || defined(__linux__)
	#define RUTAN_LINUX

#elif defined(__APPLE__) || defined(__MACH__)
	#define RUTAN_MAC
	#error "Is not supported..."

#else
	#error "Unknown platform... What are you?"
#endif

/*
	Include platform specific files
*/
#ifdef RUTAN_WINDOWS
	#define VC_EXTRALEAN
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

/*
	Defines the Graphics API
*/
#define RUTAN_D3D11
//#define RUTAN_VULKAN  // MAYBE LATER???
