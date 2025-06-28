#include "EnginePCH.h"
#include <Graphics/D3D11/D3D11Renderer.h>
#include <Core/Window.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_dx11.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <imgui_internal.h>
#include <glm/vec3.hpp>

// Link the libs
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")


namespace Rutan::Graphics
{


D3D11Renderer::D3D11Renderer()
	: m_DXGIFactory(nullptr)
	, m_Device(nullptr)
	, m_DeviceContext(nullptr)
	, m_SwapChain(nullptr)
	, m_RenderTargetView(nullptr)
	, m_Viewport()
	, m_ClearColor(0.f,0.f,0.f,0.f)
{
}

D3D11Renderer::~D3D11Renderer()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool D3D11Renderer::Init(const Rutan::Core::Window& window, const std::filesystem::path& shadersPath)
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

	glm::uvec2 windowSize = window.GetSize();

#if MSAA_LEVEL
	if (!CreateMSAAResources(windowSize))
	{
		return false;
	}
#endif
	
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
	swapChainDesc.Flags					= 0;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullscreenDesc = {};
	swapChainFullscreenDesc.Windowed = true; // TODO: change this if we want fullscreen later

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

	// Creating the camera buffer on the GPU
	D3D11_BUFFER_DESC cameraDesc = {};
	cameraDesc.ByteWidth = sizeof(glm::mat4x4);
	cameraDesc.Usage = D3D11_USAGE_DYNAMIC;
	cameraDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_Device->CreateBuffer(&cameraDesc, nullptr, &m_CameraBuffer);


	// Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


	if (!ImGui_ImplGlfw_InitForOther(window.GetWindowHandle(), true))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to load ImGui_ImplGlfw...");
		return false;
	}
	if (!ImGui_ImplDX11_Init(m_Device.Get(), m_DeviceContext.Get()))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to load ImGui_ImplDX11...");
		return false;
	}

	/* 
	#################################################################
		Hello triangle test for now. Move to other place later on
	#################################################################
	*/

	m_Viewport.TopLeftX = 0.f;
	m_Viewport.TopLeftY = 0.f;
	m_Viewport.Width    = static_cast<float>(windowSize.x);
	m_Viewport.Height   = static_cast<float>(windowSize.y);
	m_Viewport.MinDepth = 0.f;
	m_Viewport.MaxDepth = 1.f;


	m_TestShader.Load(m_Device.Get(), shadersPath.wstring() + L"/DefaultVS.hlsl", shadersPath.wstring() + L"/DefaultPS.hlsl");

	struct VertexPositionColor
	{
		glm::vec3 position;
		glm::vec4 color;
		// color as u32? u8 for each channel
	};
	constexpr VertexPositionColor vertices[] =
	{
		glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.f),
		glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 0.0f, 1.f),
		glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 1.0f, 1.f),
		glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.f),
        glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(0.0f, 0.0f, 0.0f, 1.f),
        glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(0.0f, 0.5f, 0.0f, 1.f),
        glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(0.0f, 0.5f, 0.5f, 1.f),
        glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(0.5f, 0.5f, 0.5f, 1.f) 
	};

	std::vector<u32> indices =
	{
        0, 2, 1, 0, 3, 2,  // back face
        4, 5, 6, 4, 6, 7,  // front face
        0, 1, 5, 0, 5, 4,  // bottom face
        3, 7, 6, 3, 6, 2,  // top face
        0, 4, 7, 0, 7, 3,  // left face
        1, 2, 6, 1, 6, 5   // right face
	};

	m_TestRenderData.CreateVertexBuffer(m_Device.Get(), vertices, sizeof(vertices) / sizeof(VertexPositionColor), sizeof(VertexPositionColor));
	m_TestRenderData.CreateIndexBuffer(m_Device.Get(), indices);

	return true;
}

void D3D11Renderer::Resize(const glm::uvec2& resolution)
{
	// Cleaning up old data
	m_DeviceContext->Flush();
	DestroySwapchainResources();

	HRESULT result = m_SwapChain->ResizeBuffers(0, 
                                                resolution.x, 
                                                resolution.y, 
                                                DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,
                                                0);

	m_Viewport.Width  = static_cast<float>(resolution.x);
	m_Viewport.Height = static_cast<float>(resolution.y);

	if (FAILED(result))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to recreate SwapChain buffers...");
	}

	CreateSwapchainResources();

#if MSAA_LEVEL
	DestroyMSAAResources();
	CreateMSAAResources(resolution);
#endif
}

void D3D11Renderer::SetClearColor(const glm::vec4& color)
{
	m_ClearColor = color;
}

void D3D11Renderer::SetCamera(const glm::mat4x4& cameraMatrix) const
{
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	m_DeviceContext->Map(m_CameraBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &cameraMatrix, sizeof(cameraMatrix));
	m_DeviceContext->Unmap(m_CameraBuffer.Get(), 0);

	// Bind camera to location 0
	m_DeviceContext->VSSetConstantBuffers(0, 1, m_CameraBuffer.GetAddressOf());
}

void D3D11Renderer::BeginFrame()
{
	// Clearing the screen
#if MSAA_LEVEL
	m_DeviceContext->OMSetRenderTargets(1, m_MsaaRenderTargetView.GetAddressOf(), nullptr);
	m_DeviceContext->ClearRenderTargetView(m_MsaaRenderTargetView.Get(), &m_ClearColor[0]);
#else
	m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), &m_ClearColor[0]);
#endif
	m_DeviceContext->RSSetViewports(1, &m_Viewport);
	
	// TODO: Render all the commands that was queue up
	m_TestShader.Draw(m_DeviceContext.Get(), m_TestRenderData);

	// Prepare for next ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void D3D11Renderer::EndFrame()
{
	// Draw ImGui
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
#if MSAA_LEVEL
    // Resolve MSAA texture
    m_DeviceContext->ResolveSubresource(m_Backbuffer.Get(), 0,  // Destination (swap chain back buffer)
                                        m_MsaaTexture.Get(), 0, // Source (MSAA render target)
                                        DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM);
#endif

	// TODO: Set vsync enabled/disabled from some setting
	m_SwapChain->Present(0, 0);
}

bool D3D11Renderer::CreateSwapchainResources()
{
	if (FAILED(m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&m_Backbuffer))))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to get backbuffer from swapchain...");
		return false;
	}

	if (FAILED(m_Device->CreateRenderTargetView(m_Backbuffer.Get(), nullptr, &m_RenderTargetView)))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to create render target view from backbuffer...");
		return false;
	}
	return true;
}

void D3D11Renderer::DestroySwapchainResources()
{
	m_RenderTargetView.Reset();
	m_Backbuffer.Reset();
}

#if MSAA_LEVEL
bool D3D11Renderer::CreateMSAAResources(const glm::uvec2& resolution)
{
	u32 msaaSampleCount = (u32)MSAA_LEVEL;
	u32 msaaQuality = 0;
	if (FAILED(m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, msaaSampleCount, &msaaQuality))) 
	{
		LOG_ENGINE_FATAL("D3D11: MSAA level {0} with quality {1} is not supported on your PC...", msaaSampleCount, msaaQuality);
		return false;
	}

	D3D11_TEXTURE2D_DESC colorDesc = {};
	colorDesc.Width                = resolution.x;
	colorDesc.Height               = resolution.y;
	colorDesc.Format               = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	colorDesc.SampleDesc.Count     = msaaSampleCount;
	colorDesc.SampleDesc.Quality   = msaaQuality - 1;
	colorDesc.MipLevels            = 1;
	colorDesc.ArraySize            = 1;
	colorDesc.Usage                = D3D11_USAGE_DEFAULT;
	colorDesc.BindFlags            = D3D11_BIND_RENDER_TARGET;
	if (FAILED(m_Device->CreateTexture2D(&colorDesc, nullptr, &m_MsaaTexture)))
	{
		LOG_ENGINE_FATAL("D3D11: MSAA Failed to create texture...");
		return false;
	}
	if (FAILED(m_Device->CreateRenderTargetView(m_MsaaTexture.Get(), nullptr, &m_MsaaRenderTargetView)))
	{
		LOG_ENGINE_FATAL("D3D11: MSAA Failed to create render target view...");
		return false;
	}

	// Success!
	return true;
}

void D3D11Renderer::DestroyMSAAResources()
{
	m_MsaaRenderTargetView.Reset();
	m_MsaaTexture.Reset();
}
#endif


}