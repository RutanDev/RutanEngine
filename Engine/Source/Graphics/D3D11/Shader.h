#pragma once
#include <d3d11.h>
#include <wrl/client.h>
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

namespace Rutan::Graphics
{

// Vertexshader + Pixelshader
class Shader 
{
public:
	Shader() = default;
	// TODO: Send in multiple paths as vector/array, vertex, pixel, geometry...
	Shader(ID3D11Device* device,
		   const std::filesystem::path& vertexShaderPath,
		   const std::filesystem::path& pixelShaderPath);

	void Bind(ID3D11DeviceContext* deviceContext);
	void Unbind(ID3D11DeviceContext* deviceContext);

	const bool& IsCompiled() const { return m_Compiled; };

	// Bind a constantbuffer?
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
	bool                       m_Compiled = false;
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