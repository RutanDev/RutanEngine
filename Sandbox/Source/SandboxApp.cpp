#include <RutanEngine.h>

/*
*	### Welcome to the Sandbox for RutanEngine
*
*	Here we can play around with our features and test stuff out :)
*
*/


class SandboxApp : public Rutan::Application
{
public:
	SandboxApp(const Rutan::AppSettings& appsettings)
		:Application(appsettings)
	{
	}

	~SandboxApp()
	{
	}

	// Inherited via Application
	virtual void Init() override
	{
		// Load assets
		LOG_INFO("Sandbox Initalized");
	}

	virtual void Clean() override
	{
		// Clean up assets and stuff
		LOG_INFO("Sandbox has been cleaned up");
	}

	virtual void Input() override
	{
		// What happens if we press "W"?
	}

	virtual void Update(f64 dt) override
	{
		// Scene.Update();
	}

	virtual void Render() override
	{
		// Scene.Render();
	}

	virtual void RenderGUI() override
	{
		// Render ImGUI stuff?
	}

private:
	// Store stuff related to this project here

};


int main()
{
	// Setup stuff for your application
	Rutan::AppSettings settings;
	settings.Name		  = "Sandbox";
	settings.WindowWidth  = 1600u;
	settings.WindowHeight = 900u;
	settings.Fullscreen   = false;
	settings.VSync		  = true;

	// Start application
	SandboxApp app(settings);
	return 0;
}