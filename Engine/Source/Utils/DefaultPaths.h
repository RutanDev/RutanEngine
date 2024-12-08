#pragma once
#include <filesystem>

namespace Rutan::Utils
{


class DefaultPaths
{
public:
	DefaultPaths();
	std::filesystem::path ProjectPath;
	std::filesystem::path EnginePath;
	std::filesystem::path SandboxPath;
	std::filesystem::path ShaderPath;

};


}
