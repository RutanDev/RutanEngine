#include <RutanEngine.h>
#include <IO/Keycodes.h>
#include <imgui.h>

/*
*	### Welcome to the Sandbox for RutanEngine
*
*	Here we can play around with our features and test stuff out :)
*
*/


class SandboxApp : public Rutan::Core::Application
{
public:
	SandboxApp(const Rutan::Core::AppSettings& appsettings)
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

	virtual void Input(Rutan::IO::InputHandler& input) override
	{
		// Iterate the keyboard
		for (u16 i = Rutan::IO::Keyboard::FIRST; i < Rutan::IO::Keyboard::LAST; i++)
		{
			if (input.IsKeyPressed(i))
				LOG_INFO("Keyboard: Pressed once {0}", i);
			else if (input.IsKeyHeld(i))
				LOG_INFO("Keyboard: Holding down {0}", i);
			else if (input.IsKeyReleased(i))
				LOG_INFO("Keyboard: Released once {0}", i);
		}

		// Iterate the mouse buttons
		for (u16 i = Rutan::IO::Mouse::FIRST; i < Rutan::IO::Mouse::LAST; i++)
		{
			if (input.IsKeyPressed(i))
				LOG_INFO("Mouse: Pressed once {0}", i);
			else if (input.IsKeyHeld(i))
				LOG_INFO("Mouse: Holding down {0}", i);
			else if (input.IsKeyReleased(i))
				LOG_INFO("Mouse: Released once {0}", i);
		}

		// Close application
		if (input.IsKeyPressed(Rutan::IO::Keyboard::Escape))
			StopApp();
	}

	virtual void Update(f64 dt) override
	{
		// Scene.Update();
		
		// Setting up the editor-window
        if (ImGui::BeginMainMenuBar()) 
		{
            if (ImGui::BeginMenu("File")) 
			{
                if (ImGui::MenuItem("New project")) {}
                if (ImGui::MenuItem("Open", "Ctrl+O")) {}
                if (ImGui::MenuItem("Save", "Ctrl+S")) {}
                if (ImGui::MenuItem("Save as..")) {}
				ImGui::Separator();
				if (ImGui::MenuItem("Quit")) 
				{
					StopApp();
				}
                ImGui::EndMenu();
            }
			if (ImGui::BeginMenu("Edit"))
			{
				// TODO
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{
				// TODO
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("About")) { /*Some data about this application?*/ }
				if (ImGui::MenuItem("ImGui DemoWindow")) ImGui::ShowDemoWindow();
				ImGui::EndMenu();
			}
            ImGui::EndMainMenuBar();
        }

		// TODO: Structure it better and lock the windows into place
		ImGui::Begin("Scene Hierarchy");
		ImGui::End();
		ImGui::Begin("Entity details");
		ImGui::End();
		ImGui::Begin("Content Browser");
		ImGui::End();
	}

private:
	// Store stuff related to this project here

};


int main()
{
	// Setup stuff for your application
	Rutan::Core::AppSettings settings;
	settings.Name		  = "Sandbox";
	settings.WindowWidth  = 1600u;
	settings.WindowHeight = 900u;
	settings.Fullscreen   = false;
	settings.VSync		  = true;

	// Start application
	SandboxApp sandbox(settings);
	sandbox.StartApp();
	return 0;
}