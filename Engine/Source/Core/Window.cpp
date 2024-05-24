#include "EnginePCH.h"
#include "Window.h"
#include <Core/Application.h>

namespace Rutan
{

Window::Window(const AppSettings& settings)
	: m_Name(settings.Name)
	, m_Fullscreen(settings.Fullscreen)
	, m_VSync(settings.VSync)
	, m_Width(settings.WindowWidth)
	, m_Height(settings.WindowHeight)
{
}

Window::~Window()
{
}

bool Window::Init()
{
	LOG_ENGINE_INFO("Created a window '{0}' ({1}x{2})", m_Name, m_Width, m_Height);
	return true;
}

bool Window::IsOpen()
{
	// Is keept open as long as we have not sent an close event
	return true;
}

void Window::PollEvent()
{
}

void Window::EnableVSync(bool toggle)
{
	m_VSync = toggle;
}

void Window::EnableFullscreen(bool toggle)
{
	m_Fullscreen = toggle;
}

void Window::SetName(const std::string& name)
{
	m_Name = name;
}

void Window::SetSize(u32 width, u32 height)
{
	m_Width	 = width;
	m_Height = height;
}


}