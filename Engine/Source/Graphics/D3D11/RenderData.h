#pragma once
#include <d3d11.h>

#include <wrl/client.h>
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

namespace Rutan::Graphics
{

class RenderData
{
public:
    RenderData() = default;
    
    // TODO: Make it possible to send in
    // * Only vertices
    // * Or
    // * Send in vertices + indices
    bool CreateVertexBuffer(ID3D11Device* device, const void* data, u32 vertexCount, u32 vertexStride);
    bool CreateIndexBuffer(ID3D11Device* device,  const std::vector<u32>& indices);
    void Bind(ID3D11DeviceContext* deviceContext) const;
    void UnBind(ID3D11DeviceContext* deviceContext) const;
    u32 GetIndexCount() const { return m_IndexCount; };

private:
    ComPtr<ID3D11Buffer> m_VertexBuffer;
    ComPtr<ID3D11Buffer> m_IndexBuffer;
    u32 m_VertexCount  = 0;
    u32 m_IndexCount   = 0;
    u32 m_VertexStride = 0;
};

}