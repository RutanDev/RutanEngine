#pragma once
#include <d3d11.h>
#include <dxgi1_3.h>
#include <glm/mat4x4.hpp>
#include <wrl/client.h>

// TEMP
#include <Graphics/D3D11/Shader.h>	
#include <Graphics/D3D11/RenderData.h>

// Disable: 0 
// MSAA:    2 - 16
#define MSAA_LEVEL 4

namespace std::filesystem { class path; }
namespace Rutan::Core { class Window; }

template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;


namespace Rutan::Graphics
{


class D3D11Renderer
{
public:
	D3D11Renderer();
	~D3D11Renderer();

	bool Init(const Rutan::Core::Window& window, const std::filesystem::path& shadersPath);
	void Resize(const glm::uvec2& resolution);
	void SetClearColor(const glm::vec4& color);

	// TODO: Need a better solution for uploading constant buffers
	void SetCamera(const glm::mat4x4& cameraMatrix) const;

	// Made as often as possible
	void BeginFrame();
	void EndFrame();

private:
	bool CreateSwapchainResources();
	void DestroySwapchainResources();

#if MSAA_LEVEL
	bool CreateMSAAResources(const glm::uvec2& resolution);
	void DestroyMSAAResources();
#endif

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
	ComPtr<ID3D11Texture2D>        m_Backbuffer;
	ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
	
#if MSAA_LEVEL
	ComPtr<ID3D11Texture2D>        m_MsaaTexture;
	ComPtr<ID3D11RenderTargetView> m_MsaaRenderTargetView;
#endif

	// Main camera
	ComPtr<ID3D11Buffer> m_CameraBuffer;

	// TEMP
	glm::vec4 m_ClearColor;
	D3D11_VIEWPORT m_Viewport;	// TODO: Should be connected to the camera?
	Shader m_TestShader;
	RenderData m_TestRenderData;


};


}