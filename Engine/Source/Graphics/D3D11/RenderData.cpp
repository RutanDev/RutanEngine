#include <EnginePCH.h>
#include <Graphics/D3D11/RenderData.h>

namespace Rutan::Graphics
{


bool RenderData::CreateVertexBuffer(ID3D11Device* device, const void* data, u32 vertexCount, u32 vertexStride)
{
    D3D11_BUFFER_DESC bufferInfo = {};
    bufferInfo.ByteWidth = vertexCount * vertexStride;
    bufferInfo.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
    bufferInfo.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
    bufferInfo.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA resourceData = {};
    resourceData.pSysMem = data;

    if (FAILED(device->CreateBuffer(&bufferInfo,
                                    &resourceData,
                                    &m_VertexBuffer)))
    {
        LOG_ENGINE_FATAL("D3D11: Failed to create vertex buffer");
        return false;
    }

    m_VertexCount = vertexCount;
    m_VertexStride = vertexStride;

    return true;
}

bool RenderData::CreateIndexBuffer(ID3D11Device* device, const std::vector<u32>& indices)
{
    D3D11_BUFFER_DESC bufferInfo = {};
    bufferInfo.ByteWidth = static_cast<UINT>(sizeof(u32) * indices.size());
    bufferInfo.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
    bufferInfo.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
    bufferInfo.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA resourceData = {};
    resourceData.pSysMem = indices.data();

    if (FAILED(device->CreateBuffer(&bufferInfo,
                                    &resourceData,
                                    &m_IndexBuffer)))
    {
        LOG_ENGINE_FATAL("D3D11: Failed to create index buffer");
        return false;
    }

    m_IndexCount = static_cast<u32>(indices.size());

    return true;
}

void RenderData::Bind(ID3D11DeviceContext* deviceContext) const
{   
    u32 vertexOffset = 0;
    deviceContext->IASetVertexBuffers(0, 1,
                                      m_VertexBuffer.GetAddressOf(),
                                      &m_VertexStride,
                                      &vertexOffset);

    deviceContext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void RenderData::UnBind(ID3D11DeviceContext* deviceContext) const
{
    ID3D11Buffer* nullBuffer = nullptr;
    UINT nullStride = 0;
    UINT nullOffset = 0;

    deviceContext->IASetVertexBuffers(0, 1, &nullBuffer, &nullStride, &nullOffset);
    deviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT::DXGI_FORMAT_UNKNOWN, 0);
}


}