#pragma once
#include <d3d11.h>
#include <Graphics/D3D11/RenderData.h>

#include <wrl/client.h>
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

/*
Setup a material/shader-file: BasicShader.mat

	Points/Lines/Triangles?
	Topology?

	inputLayout:  send in a struct?
	Vertexshader: "Shaders/BasicVS.hlsl"
	Pixelshader:  "Shaders/BasicPS.hlsl"
	OutputMerger???
*/

namespace Rutan::Graphics
{

// Vertexshader + Pixelshader
class Shader 
{
public:
	//TODO: Send in material-filename
	Shader() = default;

	bool Load(ID3D11Device* device,
		      const std::filesystem::path& vertexShaderPath, 
		      const std::filesystem::path& pixelShaderPath);

	// Bind a constantbuffer?

	void Draw(ID3D11DeviceContext* deviceContext, const RenderData& renderData);

	// TODO: Get the vertexStruct from shaderblob

private:
	bool CompileShader(const std::filesystem::path& filepath,
					   const std::string& entryPoint,
					   const std::string& profile,
     				   ComPtr<ID3DBlob>& shaderBlob);

	DXGI_FORMAT GetDXGIFormat(const std::string& semanticName, UINT mask) const;
	
	bool CreateInputLayout(ID3D11Device* device, 
		                   ID3DBlob* blob);

private:
	ComPtr<ID3D11InputLayout>  m_InputLayout;
	ComPtr<ID3D11VertexShader> m_VertexShader;
	ComPtr<ID3D11PixelShader>  m_PixelShader;
};


class ComputeShader
{
public:
	ComputeShader(/*Path to the shader*/) = default; // For now
	~ComputeShader() = default;

private:
	ComPtr<ID3D11ComputeShader> m_ComputeShader;

};



}