#include "EnginePCH.h"
#include <Utils/DefaultPaths.h>

namespace Rutan::Utils
{


DefaultPaths::DefaultPaths()
{
	// Path to the stard directory
	const std::filesystem::path currentPath = std::filesystem::current_path();

	// Find projectPath
	for (auto it = currentPath.begin(); it != currentPath.end(); ++it)
	{
		ProjectPath /= *it;

		// Stop right there!
		if (*it == "RutanEngine") break;
	}

	
	if (!std::filesystem::exists(ProjectPath)) {
		LOG_ENGINE_FATAL("Failed to setup default path to the project...");
		return;
	}

	EnginePath  = ProjectPath;
	SandboxPath = ProjectPath;
	EnginePath.append("Engine");
	SandboxPath.append("Sandbox");
	ShaderPath.append(EnginePath.native()).append("Source").append("Graphics");

#ifdef RUTAN_D3D11
	ShaderPath.append("D3D11").append("Shaders");
#endif
}


}