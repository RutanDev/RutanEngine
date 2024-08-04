#include "EnginePCH.h"
#include <Core/Application.h>
#include <Utils/Timer.h>
#include <Platform/Platform.h>
#include <Platform/D3D11/D3D11Graphics.h>


namespace Rutan::Core
{


Application::Application(const Rutan::Core::AppSettings& settings)
	: m_Running(false)
	, m_Window(settings)
	, m_Renderer(std::make_unique<D3D11Graphics>())
{
	if (!m_Window.Init())
	{
		LOG_ENGINE_FATAL("Window failed to initialize...");
		return;
	}

	if (!m_InputHandler.Init(m_Window.getWindowHandle()))
	{
		LOG_ENGINE_FATAL("InputHandler failed to initialize...");
		return;
	}

	if (!m_Renderer->Init(m_Window.getWindowHandle()))
	{
		LOG_ENGINE_FATAL("Renderer failed to initialize...");
		return;
	}

	m_Running = true;
}

void Application::StartApp()
{
	if (!m_Running) 
	{
		LOG_ENGINE_FATAL("Application failed to initialize...");
		return;
	}

	// Initialize the application with scenes and assets
	// that was defined in your application for example "Sandbox"
	Init();

	Timer timer;
	double dt = 0;

	// The "Game-loop"
	while (m_Running)
	{
		// Start timer
		timer.Start();
		
		// Getting window events
		m_Window.PollEvent();

		m_Renderer->ClearScreen({ 1,0,0,1 });

		// [TODO] Handle Events

		// Handling input
		Input(m_InputHandler);
		m_InputHandler.ClearInputStatus();

		// Update code
		Update(dt);

		// Render to screen
		Render();
		RenderGUI();

		m_Renderer->SwapBuffers();

		// End timer
		timer.Stop();
		dt = timer.GetMilliseconds();
	}

	// Cleaning up the application
	Clean();
}

void Application::StopApp()
{
	m_Running = false;
}


}