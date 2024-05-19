#include "SandboxApp.h"
#include "RutanEngine.h"

SandboxApp::SandboxApp(const std::string& nameOfApp)
	:Application(nameOfApp)
{
}

void SandboxApp::Init()
{
	// Load assets
	LOG_INFO("Sandbox Initalized");
}

void SandboxApp::Clean()
{
	// Clean up assets and stuff
	LOG_INFO("Sandbox has been cleaned up");
}

void SandboxApp::Input()
{
	// What happens if we press "W"?
}

void SandboxApp::Update(f64 dt)
{
	// Scene.Update();
}

void SandboxApp::Render()
{
	// Scene.Render();
}

void SandboxApp::RenderGUI()
{
	// Render ImGUI stuff?
}
