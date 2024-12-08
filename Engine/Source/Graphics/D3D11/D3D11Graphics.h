#pragma once
#include <Graphics/Renderer.h>
#include <d3d11.h>
#include <dxgi1_3.h>

#include <Graphics/D3D11/Shader.h>	// TEMP

namespace std::filesystem { class path; }


namespace Rutan::Graphics
{


class D3D11Graphics : public Renderer
{
public:
	D3D11Graphics();
	~D3D11Graphics() = default;

	virtual bool Init(const Rutan::Core::Window& window, const std::filesystem::path& shadersPath) override;
	virtual void OnResize(const glm::uvec2& resolution) override;
	virtual void ClearScreen(const glm::vec4& color) override;
	virtual void Render() override;

private:
	bool CreateSwapchainResources();
	void DestroySwapchainResources();

private:
	// Finds adapters (GPUs) for this pc and creates the swapchain
	ComPtr<IDXGIFactory2> m_DXGIFactory;		
	
	// Creates buffers, textures, samples, shaders
	ComPtr<ID3D11Device> m_Device;			
	
	// Handles draw and compute commands to the GPU
	ComPtr<ID3D11DeviceContext> m_DeviceContext;	

	// Stores rendered data - presented to an output/screen
	ComPtr<IDXGISwapChain1> m_SwapChain;

	// Pointer to a texture that D3D11 can draw to
	ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

	D3D11_VIEWPORT m_Viewport;	// TODO: Should be connected to the camera?

	Shader m_TestShader;	// TEMP
};


}