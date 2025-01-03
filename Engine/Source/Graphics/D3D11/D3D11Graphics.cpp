#include "EnginePCH.h"
#include <Graphics/D3D11/D3D11Graphics.h>
#include <Core/Window.h>
#include <glm/vec3.hpp>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_dx11.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

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
	, m_ClearColor(0.f,0.f,0.f,0.f)
{
}

D3D11Graphics::~D3D11Graphics()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool D3D11Graphics::Init(const Rutan::Core::Window& window, const std::filesystem::path& shadersPath)
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

	// Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

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

	struct VertexPositionColor
	{
		glm::vec3 position;
		glm::vec3 color;
	};

	bool createdShader = false;
	createdShader |= m_TestShader.CreateVertexShader(m_Device.Get(), shadersPath.wstring() + L"/DefaultVS.hlsl");
	createdShader |= m_TestShader.CreatePixelShader(m_Device.Get(),  shadersPath.wstring() + L"/DefaultPS.hlsl");


	// Automate this somehow as it looks like shit
	/*
		The plan
		* Send in a struct to inputLayoutFunction
		* Parser - check row by row
			* what type is it?
			* dictionary-map from typically used types to DXGI_FORMAT
			* SemanticName??? How to handle it???
	*/ 
	
	D3D11_INPUT_ELEMENT_DESC vertexInputLayoutInfo[2] =
	{
		{
			"position",
			0,
			DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			offsetof(VertexPositionColor, position),
			D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"color",
			0,
			DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			offsetof(VertexPositionColor, color),
			D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};
	createdShader |= m_TestShader.CreateInputLayout(m_Device.Get(), vertexInputLayoutInfo, 2);

	constexpr VertexPositionColor vertices[] =
	{
		glm::vec3(  0.0f,  0.5f, 0.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ),
		glm::vec3(  0.5f, -0.5f, 0.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ),
		glm::vec3( -0.5f, -0.5f, 0.0f ), glm::vec3( 0.0f, 0.0f, 1.0f )
	};

	createdShader |= m_TestShader.CreateVertexBuffer(m_Device.Get(), (void*)vertices, sizeof(vertices));

	return createdShader;
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

	m_Viewport.Width  = static_cast<float>(resolution.x);
	m_Viewport.Height = static_cast<float>(resolution.y);

	if (FAILED(result))
	{
		LOG_ENGINE_FATAL("D3D11: Failed to recreate SwapChain buffers...");
	}

	CreateSwapchainResources();
}

void D3D11Graphics::SetClearColor(const glm::vec4& color)
{
	m_ClearColor = color;
}

void D3D11Graphics::BeginFrame()
{
	// Clearing the screen
	m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), &m_ClearColor[0]);
	m_DeviceContext->RSSetViewports(1, &m_Viewport);
	
	// TODO: Render all the commands that was queue up
	// TODO: Loop through all the shaders
	m_TestShader.Bind(m_DeviceContext.Get());
	m_DeviceContext->Draw(3, 0);

	// Prepare for next ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void D3D11Graphics::EndFrame()
{
	// Draw ImGui
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	
	// TODO: Set vsync enabled/disabled from some setting
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