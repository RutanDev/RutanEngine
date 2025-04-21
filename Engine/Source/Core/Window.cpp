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
	, m_WindowSize(settings.WindowWidth, settings.WindowHeight)
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
	if (!m_WindowSize.x || !m_WindowSize.y)
	{
		const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
		
		m_WindowSize.x = videoMode->width;
		m_WindowSize.y = videoMode->height;
	}

	// Should not scale the window content
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWmonitor* fullscreenMonitor = m_Fullscreen ? primaryMonitor : nullptr;

	m_GLFWwindow = glfwCreateWindow(m_WindowSize.x, m_WindowSize.y, m_Name.c_str(), fullscreenMonitor, nullptr);
	if (!m_GLFWwindow)
	{
		LOG_ENGINE_FATAL("GLFW: Failed to create window with width({0}), height({1}), name({2}) and fullscreen({3})", m_WindowSize.x, m_WindowSize.y, m_Name, m_Fullscreen);
		glfwTerminate();
		return false;
	}
	LOG_ENGINE_INFO("Created a window '{0}' ({1}x{2})", m_Name, m_WindowSize.x, m_WindowSize.y);

	return true;
}

bool Window::IsOpen()
{
	return !glfwWindowShouldClose(m_GLFWwindow);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::SetName(const std::string& name)
{
	m_Name = name;
	glfwSetWindowTitle(m_GLFWwindow, m_Name.c_str());
}

void Window::SetSize(const glm::uvec2& windowSize)
{
	m_WindowSize.x = windowSize.x;
	m_WindowSize.y = windowSize.y;
	glfwSetWindowSize(m_GLFWwindow, m_WindowSize.x, m_WindowSize.y);
}

void Window::EnableVSync(bool toggle)
{
	m_VSync = toggle;
}

void Window::EnableFullscreen(bool toggle)
{
	m_Fullscreen = toggle;
}

GLFWwindow* Window::GetWindowHandle() const
{
	return m_GLFWwindow;
}

const glm::uvec2& Window::GetSize() const
{
	return m_WindowSize;
}


}
