#pragma once
#include <d3d11.h>

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

class Shader 
{
public:
	Shader(/* Device, Materialpath */);	//TODO: Send in material-filename
	~Shader() = default;

	void Bind(ID3D11DeviceContext* deviceContext);
	void UnBind(ID3D11DeviceContext* deviceContext);


	// TODO: Will be private later on
	bool CreateVertexShader(ID3D11Device* device,
							const std::filesystem::path& filepath);
	bool CreatePixelShader(ID3D11Device* device,
						   const std::filesystem::path& filepath);

	// Send in a vertexstruct??? Can it be read from the blobb???
	bool CreateInputLayout(ID3D11Device* device, 
						   D3D11_INPUT_ELEMENT_DESC* vertexLayout, 
						   u32 nrOfInputElements);

	bool CreateVertexBuffer(ID3D11Device* device, void* data, u32 byteWidth);

	void SetViewport(D3D11_VIEWPORT* viewport);

	
private:
	bool CompileShader(const std::filesystem::path& filepath,
					   const std::string& entryPoint,
					   const std::string& profile,
     				   ComPtr<ID3DBlob>& shaderBlob);


private:
	ComPtr<ID3D11InputLayout>  m_InputLayout;
	ComPtr<ID3D11VertexShader> m_VertexShader;
	ComPtr<ID3DBlob>		   m_VertexBlob;
	ComPtr<ID3D11Buffer>	   m_VertexBuffer;
	ComPtr<ID3D11PixelShader>  m_PixelShader;

	// Low prio
	// ComputeShader
	// GeometryShader - prob. not necessary
};

}