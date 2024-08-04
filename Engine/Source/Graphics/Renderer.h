#pragma once

struct GLFWwindow;

class Renderer
{
public:
	// Common interface
	virtual bool Init(GLFWwindow* windowHandle) = 0;
	virtual void ClearScreen(std::array<float, 4> color) = 0;
	virtual void SwapBuffers() = 0;
	virtual void Draw() = 0;
};