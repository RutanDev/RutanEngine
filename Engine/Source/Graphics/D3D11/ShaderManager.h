#include <Graphics/D3D11/Shader.h>

/*
Setup a material/shader-file: BasicShader.mat

	Points/Lines/Triangles?
	Topology?

	inputLayout:  send in a struct?
	Vertexshader: "Shaders/BasicVS.hlsl"
	Pixelshader:  "Shaders/BasicPS.hlsl"
	OutputMerger???
*/

struct ID3D11Device;

namespace Rutan::Graphics
{

class ShaderManager
{
public:
	ShaderManager() = default;
	bool LoadAllShaders(ID3D11Device* device, 
                        const std::filesystem::path& shaderFolderPath);

	const std::vector<Shader>& GetAllShaders() const { return m_Shaders; }

private:
	void LoadShader(ID3D11Device* device,
	                const std::filesystem::path& shaderFolderPath, 
	                const std::string& shadername);

private:
	std::vector<Shader> m_Shaders;
	std::unordered_map<std::string, u8> m_ShadernameToID;

};



}

