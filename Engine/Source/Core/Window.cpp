#include "EnginePCH.h"
#include "Window.h"

namespace Rutan
{

Window::Window()
	: m_Fullscreen(false)
	, m_VSync(true)
	, m_Caption("RutanEngine")
	, m_Size({ 0,0 })
{
}

Window::~Window()
{
}

bool Window::Init()
{
	// TODO: Read from init-file?
	m_Size.width  = 1600;
	m_Size.height = 900;

	LOG_ENGINE_INFO("Created a window '{0}' ({1}x{2})", m_Caption, m_Size.width, m_Size.height);

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

void Window::SetCaption(const std::string& caption)
{
	m_Caption = caption;
}


}