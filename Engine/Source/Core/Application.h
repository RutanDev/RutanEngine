#pragma once
#include <Core/Window.h>
#include <Core/Types.h>
#include <Graphics/Renderer.h>
#include <memory>


namespace Rutan
{

struct AppSettings
{
	std::string Name		 = "Rutan";
	u32			WindowWidth  = 1600;
	u32			WindowHeight = 900;
	bool		Fullscreen	 = false;
	bool		VSync		 = true;
	bool		Resizable	 = true;
	bool		EnableImGui  = true;
};


class Application
{
public:
	Application(const Rutan::AppSettings& settings);
	~Application() = default;

	// Should not be possible to copy or assign.
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	// Setup data specific for this application
	virtual void Init() = 0;
	// Clean up data when closing application
	virtual void Clean() = 0;
	// Setup how input should be handled
	virtual void Input() = 0;
	// Update the scene with all the entities
	virtual void Update(f64 dt) = 0;
	// Render the models
	virtual void Render() = 0;
	// Render imGUI stuff
	virtual void RenderGUI() = 0;

private:
	void Run();

private:
	// Handling the surface to draw on
	Window m_Window;

	// InputHandler
	// - Handling input

	// - Closest contact with the Graphics API
	std::unique_ptr<Renderer> m_Renderer;

	// Scenehandler
	// - Using an ECS with all the components.

	// ScriptComponent
	// - Update anything if needed

};


}
