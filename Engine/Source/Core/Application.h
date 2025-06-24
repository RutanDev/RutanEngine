#pragma once
#include <Core/Window.h>
#include <Core/Types.h>
#include <IO/InputHandling.h>
#include <Utils/DefaultPaths.h>
#include <Scene/SceneHandler.h>
#include <Graphics/D3D11/D3D11Renderer.h>
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
	bool		EnableImGui  = true; //TODO: Make it possible to disable ImGui for performance
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
	// Update the scene with all the entities
	virtual void Update(f64 dt) = 0;
	
private:
	void SetupGLFWCallback();

// Can be used in the application
protected:
	IO::InputHandler     InputHandler;
	Scene::SceneHandler  SceneHandler;
	Rutan::Scene::Entity ActiveCamera;

	// AudioSystem/AudioHandler
	// Some handler for adding Shaders?
	// Some handler for adding scripts?

private:
	bool                    m_Running;
	Utils::DefaultPaths     m_DefaultPaths;
	Window                  m_Window;
	Graphics::D3D11Renderer m_Renderer;

};


}
