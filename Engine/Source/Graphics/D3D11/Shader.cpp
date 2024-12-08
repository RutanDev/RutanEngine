#include "EnginePCH.h"
#include <Graphics/D3D11/Shader.h>
#include <d3dcompiler.h>

namespace Rutan::Graphics
{

Shader::Shader()
{
	// Init from the materialfile
}

void Shader::Bind(ID3D11DeviceContext* deviceContext)
{
    // Bind InputLayout
    deviceContext->IASetInputLayout(m_InputLayout.Get());


    u32 vertexStride = (4 * 3) * 2; // TODO: Precalc when setting it up
    u32 vertexOffset = 0;
    deviceContext->IASetVertexBuffers(0, 1,
                                      m_VertexBuffer.GetAddressOf(),
                                      &vertexStride,
                                      &vertexOffset);

    // TODO: Setup later
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    deviceContext->VSSetShader(m_VertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(m_PixelShader.Get(), nullptr, 0);
}

void Shader::UnBind(ID3D11DeviceContext* deviceContext)
{
    deviceContext->IASetInputLayout(nullptr);
    deviceContext->IASetVertexBuffers(0, 1, nullptr, 0, 0);
    deviceContext->VSSetShader(nullptr, nullptr, 0);
    deviceContext->PSSetShader(nullptr, nullptr, 0);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED);

    // Or maybe just use this function???
    //deviceContext->ClearState();
}

bool Shader::CreateInputLayout(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* vertexLayout, u32 nrOfInputElements)
{
    if (FAILED(device->CreateInputLayout(vertexLayout,
                                         nrOfInputElements,
                                         m_VertexBlob->GetBufferPointer(),
                                         m_VertexBlob->GetBufferSize(),
                                         &m_InputLayout)))
    {
        LOG_ENGINE_ERROR("D3D11: Failed to create vertex input layout");
        return false;
    }

    return true;
}

bool Shader::CreateVertexBuffer(ID3D11Device* device, void* data, u32 byteWidth)
{
    D3D11_BUFFER_DESC bufferInfo = {};
    bufferInfo.ByteWidth = byteWidth;
    bufferInfo.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
    bufferInfo.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA resourceData = {};
    resourceData.pSysMem = data;
    
    if (FAILED(device->CreateBuffer(&bufferInfo,
                                    &resourceData,
                                    &m_VertexBuffer)))
    {
        LOG_ENGINE_FATAL("D3D11: Failed to create triangle vertex buffer");
        return false;
    }

    return true;
}

bool Shader::CreateVertexShader(ID3D11Device* device, const std::filesystem::path& filepath)
{
    if (!CompileShader(filepath, "Main", "vs_5_0", m_VertexBlob))
    {
        return false;
    }

    HRESULT result = device->CreateVertexShader(m_VertexBlob->GetBufferPointer(),
                                                m_VertexBlob->GetBufferSize(),
                                                nullptr,
                                                &m_VertexShader);

    if (FAILED(result))
    {
        LOG_ENGINE_ERROR("D3D11: Failed to compile vertex shader");
        return false;
    }

    return true;
}

bool Shader::CreatePixelShader(ID3D11Device* device, const std::filesystem::path& filepath)
{
    ComPtr<ID3DBlob> pixelShaderBlob;

    if (!CompileShader(filepath, "Main", "ps_5_0", pixelShaderBlob))
    {
        return false;
    }

    HRESULT result = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(),
                                               pixelShaderBlob->GetBufferSize(),
                                               nullptr,
                                               &m_PixelShader);

    if (FAILED(result))
    {
        LOG_ENGINE_ERROR("D3D11: Failed to compile pixel shader");
        return false;
    }

    return true;
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