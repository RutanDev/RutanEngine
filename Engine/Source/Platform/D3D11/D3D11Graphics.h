#pragma once
#include <Graphics/Renderer.h>

class D3D11Graphics : public Renderer
{
public:
	D3D11Graphics();
	~D3D11Graphics() = default;

	virtual bool Init(GLFWwindow* windowHandle) override;
	virtual void ClearScreen(std::array<float, 4> color) override;
	virtual void SwapBuffers() override;
	virtual void Draw() override;

private:
	ComPtr<ID3D11Device>			m_Device;
	ComPtr<ID3D11DeviceContext>		m_DeviceContext;
	ComPtr<IDXGISwapChain1>			m_SwapChain;
	ComPtr<ID3D11RenderTargetView>	m_MainRenderTarget;
	ComPtr<IDXGIFactory2>			m_DXGIFactory;
	

};