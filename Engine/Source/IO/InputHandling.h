#pragma once
#include <glm/vec2.hpp>

struct GLFWwindow;


namespace Rutan::IO
{


class InputHandler
{
public:
	bool Init(GLFWwindow* windowHandle);

	bool IsKeyPressed(u16 key);  // Pressed once
	//bool IsKeyReleased(u16 key); // Released once. TODO: Not working yet

	void EnableCursor();
	void DisableCursor();
	glm::dvec2 CenterCursor() const;

	glm::dvec2 GetMousePosition() const;
	glm::dvec2 GetMouseDelta() const;

private:
	GLFWwindow* m_GLFWwindow        = nullptr;
	float       m_MouseSensitivity  = 0.1f;
	bool        m_CursorEnabled     = true;

};


}