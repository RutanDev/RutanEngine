#pragma once
#include <string>
#include <Core/Types.h>


struct GLFWwindow;


namespace Rutan::Core
{
struct AppSettings;


class Window
{
public:
	Window(const Rutan::Core::AppSettings& settings);
	~Window();
	bool Init();

	// Basic - needed in most cases
	bool IsOpen();
	void PollEvent();

	// Adjust window settings
	void SetName(const std::string& name);
	void SetSize(u32 width, u32 height);
	void EnableVSync(bool toggle = true);
	void EnableFullscreen(bool toggle = true);

	// Getters
	GLFWwindow* getWindowHandle() const;

private:
	GLFWwindow* m_GLFWwindow;
	std::string m_Name;
	bool		m_Fullscreen;
	bool		m_VSync;

	// [TODO] Use vector2 when we have it
	u32 m_Width;
	u32 m_Height;
};


}
