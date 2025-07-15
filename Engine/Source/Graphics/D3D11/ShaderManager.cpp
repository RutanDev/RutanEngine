#include "EnginePCH.h"
#include <Graphics/D3D11/ShaderManager.h>

namespace Rutan::Graphics
{

bool ShaderManager::LoadAllShaders(ID3D11Device* device, 
	                               const std::filesystem::path& shaderFolderPath)
{
	LoadShader(device, shaderFolderPath, "Default");
	//LoadShader(device, shaderFolderPath, "Opaque");
	//LoadShader(device, shaderFolderPath, "Transparent");
	//LoadComputeShader(device, shaderFolderPath, "AutomaticExposure");

	// Check if any shader failed...
	bool allShadersLoaded = false;
	for (const auto& shader : m_Shaders)
	{
		allShadersLoaded &= shader.IsCompiled();
	}
	return allShadersLoaded;
}

void ShaderManager::LoadShader(ID3D11Device* device,
	                             const std::filesystem::path& shaderFolderPath, 
	                             const std::string& shadername)
{
	if (m_ShadernameToID.find(shadername) != m_ShadernameToID.end())
	{
		LOG_ENGINE_WARN("Shader with name '{0}' already exist...");
	}

	std::filesystem::path vertexShaderPath(shaderFolderPath);
	vertexShaderPath.append(shadername + ".vs");	
	std::filesystem::path pixelShaderPath(shaderFolderPath);
	pixelShaderPath.append(shadername + ".ps");

	m_ShadernameToID[shadername] = static_cast<u8>(m_Shaders.size());
	m_Shaders.push_back(Shader(device, vertexShaderPath, pixelShaderPath));
}



}