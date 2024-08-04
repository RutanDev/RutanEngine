#pragma once
#include <array>
#include <queue>

struct GLFWwindow;


namespace Rutan::IO
{


class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	bool Init(GLFWwindow* windowHandle);

	bool IsKeyPressed(u16 key);  // Once
	bool IsKeyHeld(u16 key);     // Repeated
	bool IsKeyReleased(u16 key); // Once

	void ClearInputStatus();

private:
	GLFWwindow*         m_GLFWwindow;
	std::array<u8, 500> m_InputStatus;
	std::queue<u16>     m_InputQueue;
	//TODO: vec2        m_MousePos;

};


}