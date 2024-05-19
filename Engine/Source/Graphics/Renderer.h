#pragma once

class Renderer
{
public:
	virtual bool Init() = 0;
	virtual void ClearScreen(std::array<float, 4> color) = 0;
	virtual void SwapBuffers() = 0;
	virtual void Draw() = 0;
};