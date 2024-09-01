#include "EnginePCH.h"
#include <Platform/D3D11/D3D11Graphics.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Core/Window.h>

// Link the libs
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")


namespace Rutan::Graphics
{


D3D11Graphics::D3D11Graphics()
	: m_DXGIFactory(nullptr)
	, m_Device(nullptr)
	, m_DeviceContext(nullptr)
	, m_SwapChain(nullptr)
	, m_RenderTargetView(nullptr)
	, m_Viewport()
{
}

bool D3D11Graphics::Init(const Rutan::Core::Window& window)
{
	// Create a DXGI factory
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&m_DXGIFactory))))
	{
		LOG_ENGINE_FATAL("DXGI: Failed to create DXGIFactory...");
		return false;
	}

	// Set minimum version of DirectX 11
	constexpr D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	// Creating the device and device context
	HRESULT result = D3D11CreateDevice(nullptr,
									   D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
									   nullptr,
									   0,
									   &deviceFeatureLevel,
									   1,
									   D3D11_SDK_VERSION,
									   &m_Device,
									   nullptr,
									   &m_DeviceContext);

	if (FAILED(result))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to create device and device context...");
		return false;
	}

	glm::uvec2 windowSize    = window.GetSize();
	
	// Creating the swapchain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width					= windowSize.x;
	swapChainDesc.Height				= windowSize.y;
	swapChainDesc.Format				= DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count		= 1;
	swapChainDesc.SampleDesc.Quality	= 0;
	swapChainDesc.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount			= 2;	// Doublebuffering to avoid tearing and flickers
	swapChainDesc.SwapEffect			= DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Scaling				= DXGI_SCALING::DXGI_SCALING_STRETCH;
	swapChainDesc.Flags					= {};

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullscreenDesc = {};
	swapChainFullscreenDesc.Windowed = true; // TODO: change this if we want fullscreen later
	//swapChainFullscreenDesc.RefreshRate	 //	TODO: maybe set it here?

	result = m_DXGIFactory->CreateSwapChainForHwnd(m_Device.Get(),
												   glfwGetWin32Window(window.GetWindowHandle()),
												   &swapChainDesc,
												   &swapChainFullscreenDesc,
												   nullptr,
												   &m_SwapChain);

	if (FAILED(result))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to create swapchain...");
		return false;
	}

	if (!CreateSwapchainResources())
	{
		return false;
	}

	m_Viewport.TopLeftX = 0.f;
	m_Viewport.TopLeftY = 0.f;
	m_Viewport.Width	= static_cast<float>(windowSize.x);
	m_Viewport.Height	= static_cast<float>(windowSize.y);
	m_Viewport.MinDepth = 0.f;
	m_Viewport.MaxDepth = 1.f;

	return true;
}

void D3D11Graphics::OnResize(const glm::uvec2& resolution)
{
	// Cleaning up old data
	m_DeviceContext->Flush();
	DestroySwapchainResources();

	HRESULT result = m_SwapChain->ResizeBuffers(0, 
												resolution.x, 
												resolution.y, 
												DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,
												0);

	if (FAILED(result))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to recreate SwapChain buffers...");
	}

	CreateSwapchainResources();
}

void D3D11Graphics::ClearScreen(const glm::vec4& color)
{
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), &color[0]);
}

void D3D11Graphics::Render()
{
	// TODO: Render all the commands that was queue up

	// TODO: Fix this, first version of it for now...
	m_DeviceContext->RSSetViewports(1, &m_Viewport);
	m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
	m_SwapChain->Present(1, 0);
}

bool D3D11Graphics::CreateSwapchainResources()
{
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	if (FAILED(m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to get backbuffer from swapchain...");
		return false;
	}

	if (FAILED(m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTargetView)))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to create render target view from backbuffer...");
		return false;
	}
	return true;
}

void D3D11Graphics::DestroySwapchainResources()
{
	m_RenderTargetView.Reset();
}


}