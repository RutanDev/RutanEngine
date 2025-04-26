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
		: Application(appsettings)
		, m_Settings(appsettings)
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

		m_Camera = SceneHandler.CreateEntity();
		auto& cam = SceneHandler.AddComponent<Rutan::Scene::Components::Camera>(m_Camera);
		cam.Resolution  = glm::uvec2(m_Settings.WindowWidth, m_Settings.WindowHeight);
		cam.FieldOfView = 60.f;
		cam.Position    = glm::vec3(0.f, 0.f, -5.f);
		cam.Active      = true;

		// SetEntityModel(entity0, "TheModel.fbx");
		// SetEntityAnimations(entity0, "SomeAnimationIdle", "Idle");
		// ChangeAnimation(entity0, "idle")
	}

	virtual void Clean() override
	{
		// Clean up assets and stuff
		LOG_INFO("Sandbox has been cleaned up");
	}

	virtual void Update(f64 dt) override
	{
		if (auto cam = SceneHandler.GetComponent<Rutan::Scene::Components::Camera>(m_Camera)) 
		{
			float camSpeed = 10.f;
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::ShiftLeft))
				camSpeed *= 2.f;
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::AltLeft))
				camSpeed *= 0.5;
			float camVelocity = float(camSpeed * dt);

			// Keyboard movement
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::W))
				cam->MoveForward(camVelocity);
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::S))
				cam->MoveBackward(camVelocity);
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::D))
				cam->MoveRight(camVelocity);
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::A))
				cam->MoveLeft(camVelocity);
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::Space))
			    cam->MoveUp(camVelocity);
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::ControlLeft))
				cam->MoveDown(camVelocity);

			float rotationSpeed = 45.f; // 5 degrees per second?
			float rotationVelocity = rotationSpeed * static_cast<float>(dt);
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::Up))
				cam->Rotate(0.f, rotationVelocity, 0.f);
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::Down))
				cam->Rotate(0.f, -rotationVelocity, 0.f);
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::Left))
				cam->Rotate(rotationVelocity, 0.f, 0.f);
			if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::Right))
				cam->Rotate(-rotationVelocity, 0.f, 0.f);

			// TODO: Mouse later on
		}
		
		/*for (u16 i = Rutan::IO::Keyboard::FIRST; i < Rutan::IO::Keyboard::LAST; i++)
		{
			if (InputHandler.IsKeyPressed(i))
				LOG_INFO("Keyboard: Pressed once {0}", i);
			if (InputHandler.IsKeyReleased(i))
				LOG_INFO("Keyboard: Released once {0}", i);
		}*/

		// Iterate the mouse buttons
		/*for (u16 i = Rutan::IO::Mouse::FIRST; i < Rutan::IO::Mouse::LAST; i++)
		{
			if (InputHandler.IsKeyPressed(i))
				LOG_INFO("Mouse: Pressed once {0}", i);
			if (InputHandler.IsKeyReleased(i))
				LOG_INFO("Mouse: Released once {0}", i);
		}*/

		// Close application
		if (InputHandler.IsKeyPressed(Rutan::IO::Keyboard::Escape))
			StopApp();


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
				static bool imguiDemoStatus = false;
				ImGui::Checkbox("ImGui Demo", &imguiDemoStatus);
				if (imguiDemoStatus) { ImGui::ShowDemoWindow(); }
				
				ImGui::EndMenu();
			}


			// Add spacing to push the text to the right
			ImGui::Dummy(ImVec2(ImGui::GetWindowSize().x - ImGui::GetCursorPosX() - 100, 0));
			// FPS counter
			ImGui::Text("FPS: %u", static_cast<u32>(1.f / dt));

            ImGui::EndMainMenuBar();
        }

		// TODO: Structure it better and lock the windows into place
		/*ImGui::Begin("Scene Hierarchy");
		ImGui::End();
		ImGui::Begin("Entity details");
		ImGui::End();
		ImGui::Begin("Content Browser");
		ImGui::End();*/
	}

private:
	Rutan::Core::AppSettings m_Settings;

	// Store stuff related to this project here
	Rutan::Scene::Entity m_Camera;
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