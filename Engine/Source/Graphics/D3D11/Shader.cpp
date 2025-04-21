#include "EnginePCH.h"
#include <Graphics/D3D11/Shader.h>
#include <d3dcompiler.h>

namespace Rutan::Graphics
{

bool Shader::Load(ID3D11Device* device,
		          const std::filesystem::path& vertexShaderPath, 
		          const std::filesystem::path& pixelShaderPath)
{
    ComPtr<ID3DBlob> vertexBlob;
    ComPtr<ID3DBlob> pixelBlob;
    
    // Compiling shaders
    bool compiled = true;
    compiled |= CompileShader(vertexShaderPath, "Main", "vs_5_0", vertexBlob);
    compiled |= CompileShader(pixelShaderPath, "Main", "ps_5_0", pixelBlob);
    if (!compiled)
    {
        LOG_ENGINE_ERROR("D3D11: Failed to compile shader...");
        return false;
    }

    // Creating shaders
    HRESULT result = 0;
    result |= device->CreateVertexShader(vertexBlob->GetBufferPointer(),
                                         vertexBlob->GetBufferSize(),
                                         nullptr,
                                         &m_VertexShader);
    result |= device->CreatePixelShader(pixelBlob->GetBufferPointer(),
                                        pixelBlob->GetBufferSize(),
                                        nullptr,
                                        &m_PixelShader);
    if (FAILED(result)) 
    {
        LOG_ENGINE_ERROR("D3D11: Failed to create shader...");
        return false;
    }

    // Input Layout
    if (!CreateInputLayout(device, vertexBlob.Get()))
    {
        LOG_ENGINE_ERROR("D3D11: Failed to create input layout...");
        return false;
    }

    return true;
}

void Shader::Draw(ID3D11DeviceContext* deviceContext, const RenderData& renderData)
{
    // Binding data
    deviceContext->IASetInputLayout(m_InputLayout.Get());
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // TODO: Setup later
    deviceContext->VSSetShader(m_VertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(m_PixelShader.Get(), nullptr, 0);
    renderData.Bind(deviceContext);


    // Draw
    deviceContext->DrawIndexed(renderData.GetIndexCount(), 0, 0);


    // Unbind data
    deviceContext->IASetInputLayout(nullptr);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED);
    deviceContext->VSSetShader(nullptr, nullptr, 0);
    deviceContext->PSSetShader(nullptr, nullptr, 0);
    renderData.UnBind(deviceContext);

    // Or maybe just use this function???
    //deviceContext->ClearState();
}

DXGI_FORMAT Shader::GetDXGIFormat(const std::string& semanticName, UINT mask) const
{
    if (semanticName == "POSITION")
        return DXGI_FORMAT_R32G32B32_FLOAT;

    /*else if (semanticName == "COLOR")
        return DXGI_FORMAT_R8G8B8A8_UNORM;*/
    else if (semanticName == "COLOR")
        return DXGI_FORMAT_R32G32B32A32_FLOAT;

    else if (semanticName == "HDRCOLOR")
        return DXGI_FORMAT_R32G32B32A32_FLOAT;

    else if (semanticName == "NORMAL")
        return DXGI_FORMAT_R32G32B32_FLOAT;
    else if (semanticName == "TANGENT")
        return DXGI_FORMAT_R32G32B32_FLOAT;
    else if (semanticName == "BITANGENT")
        return DXGI_FORMAT_R32G32B32_FLOAT;

    else if (semanticName == "TEXCOORD")
        return DXGI_FORMAT_R32G32_FLOAT;

    else if (semanticName == "INSTANCEID")
        return DXGI_FORMAT_R32_UINT;

    // No matching name - go for default
    else if (mask == 0x1)   // 0001
        return DXGI_FORMAT_R32_FLOAT;
    else if (mask == 0x3)   // 0011
        return DXGI_FORMAT_R32G32_FLOAT;
    else if (mask == 0x7)   // 0111
        return DXGI_FORMAT_R32G32B32_FLOAT;
    else if (mask == 0xF)   // 1111
        return DXGI_FORMAT_R32G32B32A32_FLOAT;

    // Epic fail...
    return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
}

bool Shader::CreateInputLayout(ID3D11Device* device, ID3DBlob* vsBlob)
{
    // Reflection makes it possible to inspect metadata in the shadercode
    ComPtr<ID3D11ShaderReflection> reflection;
    D3DReflect(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), IID_PPV_ARGS(&reflection));

    // Get input signature size and count
    D3D11_SHADER_DESC shaderDesc;
    reflection->GetDesc(&shaderDesc);

    std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
    layout.reserve((size_t)shaderDesc.InputParameters);

    // Loop through all input parameters and create the input layout
    for (UINT i = 0; i < shaderDesc.InputParameters; ++i) 
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.Format = GetDXGIFormat(paramDesc.SemanticName, paramDesc.Mask); // Custom
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; // Automatically calculate offset
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;     // TODO: What if instancing?
        elementDesc.InstanceDataStepRate = 0;

        layout.push_back(elementDesc);
    }

    // Create the input layout based on the reflection data
    HRESULT result = device->CreateInputLayout(layout.data(), (UINT)layout.size(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_InputLayout);
    return SUCCEEDED(result);
}

bool Shader::CompileShader(const std::filesystem::path& filepath, const std::string& entryPoint, const std::string& profile, ComPtr<ID3DBlob>& shaderBlob)
{
	// TODO: Play around with the flags - some optimization-flags that could be useful?
    constexpr u32 compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;

    ComPtr<ID3DBlob> tempShaderBlob = nullptr;
    ComPtr<ID3DBlob> errorBlob      = nullptr;

    HRESULT result = D3DCompileFromFile(filepath.wstring().data(),
                                        nullptr,
                                        D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                        entryPoint.data(),
                                        profile.data(),
                                        compileFlags,
                                        0,
                                        &tempShaderBlob,
                                        &errorBlob);

    if (FAILED(result))
    {
        if (errorBlob)
        {
            std::string test = static_cast<const char*>(errorBlob->GetBufferPointer());
            LOG_ENGINE_ERROR("D3D11: Shader failed... {0}", test.c_str());
            errorBlob->Release();
        }
        else 
        {
            LOG_ENGINE_ERROR("D3D11: Failed to read shader '{0}' from file...", filepath.string());
        }

        return false;
    }

    shaderBlob = std::move(tempShaderBlob);
    return true;
}


}