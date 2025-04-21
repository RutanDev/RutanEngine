#pragma once

struct GLFWwindow;


namespace Rutan::IO
{


class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	bool Init(GLFWwindow* windowHandle);

	bool IsKeyPressed(u16 key);  // Pressed once
	//bool IsKeyReleased(u16 key); // Released once. TODO: Not working yet

private:
	GLFWwindow* m_GLFWwindow;
	//TODO: vec2 m_MousePos;

};


}