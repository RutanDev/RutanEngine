#include "EnginePCH.h"
#include "Window.h"
#include <Core/Application.h>
#include <GLFW/glfw3.h>

namespace Rutan::Core
{


Window::Window(const Rutan::Core::AppSettings& settings)
	: m_Name(settings.Name)
	, m_Fullscreen(settings.Fullscreen)
	, m_VSync(settings.VSync)
	, m_Width(settings.WindowWidth)
	, m_Height(settings.WindowHeight)
	, m_GLFWwindow(nullptr)
{
}

Window::~Window()
{
	glfwDestroyWindow(m_GLFWwindow);
	glfwTerminate();
}

bool Window::Init()
{
	if (!glfwInit())
	{
		LOG_ENGINE_ERROR("GLFW: Init failed...");
		glfwTerminate();
		return false;
	}

	// Getting the primary monitor
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

	// Resolution not set... Getting the resolution of the primary monitor
	if (!m_Width || !m_Height)
	{
		const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
		m_Width  = videoMode->width;
		m_Height = videoMode->height;
	}

	// Should not scale the window content
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWmonitor* fullscreenMonitor = m_Fullscreen ? primaryMonitor : nullptr;

	m_GLFWwindow = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), fullscreenMonitor, nullptr);
	if (!m_GLFWwindow)
	{
		LOG_ENGINE_INFO("GLFW: Failed to create window with width({0}), height({1}), name({2}) and fullscreen({3})", m_Width, m_Height, m_Name, m_Fullscreen);
		glfwTerminate();
		return false;
	}
	LOG_ENGINE_INFO("Created a window '{0}' ({1}x{2})", m_Name, m_Width, m_Height);

	// Setting up GLFW callback functions
	glfwSetWindowSizeCallback(m_GLFWwindow, [](GLFWwindow* window, int width, int height) 
	{
		LOG_ENGINE_INFO("Resized window to ({0}x{1})", width, height);
		glfwSetWindowSize(window, width, height);
		//TODO: Resize everything in the Renderer
		//TODO: Update the m_Width, m_Height
	});

	return true;
}

bool Window::IsOpen()
{
	return !glfwWindowShouldClose(m_GLFWwindow);
}

void Window::PollEvent()
{
	glfwPollEvents();
}

void Window::EnableVSync(bool toggle)
{
	m_VSync = toggle;
}

void Window::EnableFullscreen(bool toggle)
{
	m_Fullscreen = toggle;
}

GLFWwindow* Window::getWindowHandle() const
{
	return m_GLFWwindow;
}

void Window::SetName(const std::string& name)
{
	m_Name = name;
	glfwSetWindowTitle(m_GLFWwindow, m_Name.c_str());
}

void Window::SetSize(u32 width, u32 height)
{
	m_Width	 = width;
	m_Height = height;
	glfwSetWindowSize(m_GLFWwindow, m_Width, m_Height);
}


}
