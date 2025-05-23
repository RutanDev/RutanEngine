#include "EnginePCH.h"
#include <Core/Application.h>
#include <Utils/DeltaClock.h>
#include <Platform/Platform.h>
#include <backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>


namespace Rutan::Core
{


Application::Application(const Rutan::Core::AppSettings& settings)
	: m_Running(true)
	, m_Window(settings)
{
	m_Running &= m_Window.Init();
	m_Running &= InputHandler.Init(m_Window.GetWindowHandle());
	m_Running &= m_Renderer.Init(m_Window, m_DefaultPaths.ShaderPath);
	SetupGLFWCallback();

	// Check that everything was initialized
	if (!m_Running)
	{
		LOG_ENGINE_FATAL("Application failed to initialize...");
		return;
	}

	m_Renderer.SetClearColor(glm::vec4(1.f, 0.7f, 0.f, 1.f));
}

void Application::StartApp()
{
	// Initialize the application with scenes and assets
	// that was defined in your application for example "Sandbox"
	Init();

	DeltaClock dt;

	// The "Game-loop"
	while (m_Running)
	{
		// Getting window events
		m_Window.PollEvents();

		SceneHandler.UpdateSystems();

		// TODO: Only update when new data has been recieved
		m_Renderer.SetCamera(SceneHandler.GetCameraMatrix());

		m_Renderer.BeginFrame();
		Update(dt.GetSeconds());
		m_Renderer.EndFrame();
	}

	// Cleaning up the application
	Clean();
}

void Application::StopApp()
{
	m_Running = false;
}


void Application::SetupGLFWCallback()
{
	GLFWwindow* windowHandle = m_Window.GetWindowHandle();
	glfwSetWindowUserPointer(windowHandle, this);

	// Window was resized
	glfwSetWindowSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height)
	{
		//LOG_ENGINE_INFO("D3D11: Resized window to({0}x{1})", width, height); // TODO: Remove when we know it works
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->m_Window.SetSize(glm::uvec2(width, height));
	});
	
	// Resizing the framebuffer
	glfwSetFramebufferSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height)
	{
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		app->m_Renderer.OnResize(glm::uvec2(width, height));
	});	
}

}