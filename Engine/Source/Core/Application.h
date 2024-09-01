#pragma once
#include <Core/Window.h>
#include <Core/Types.h>
#include <IO/InputHandling.h>
#include <Graphics/Renderer.h>
#include <memory>

namespace Rutan::Core
{

struct AppSettings
{
	std::string Name		 = "Rutan";
	u32			WindowWidth  = 0;
	u32			WindowHeight = 0;
	bool		Fullscreen	 = false;
	bool		VSync		 = true;
	bool		Resizable	 = true;
	bool		EnableImGui  = true;
};


class Application
{
public:
	Application(const Rutan::Core::AppSettings& settings);
	~Application() = default;

	// Should not be possible to copy or assign.
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void StartApp();
	void StopApp();

	// Setup data specific for this application
	virtual void Init() = 0;
	// Clean up data when closing application
	virtual void Clean() = 0;
	// Setup how input should be handled
	virtual void Input(Rutan::IO::InputHandler& inputHandler) = 0;
	// Update the scene with all the entities
	virtual void Update(f64 dt) = 0;
	// Render the models
	virtual void Render() = 0;
	// Render imGUI stuff
	virtual void RenderGUI() = 0;

private:
	void SetupGLFWCallback();

private:
	bool             m_Running;
	Window           m_Window;
	IO::InputHandler m_InputHandler;

	// - Closest contact with the Graphics API
	std::unique_ptr<Graphics::Renderer> m_Renderer;

	// Scenehandler
	// - Using an ECS with all the components.

	// ScriptComponent
	// - Update anything if needed

};


}
