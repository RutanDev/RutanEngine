#include "EnginePCH.h"
#include <IO/InputHandling.h>
#include <IO/Keycodes.h>
#include <GLFW/glfw3.h>

namespace Rutan::IO
{


bool InputHandler::Init(GLFWwindow* windowHandle)
{
	m_GLFWwindow = windowHandle;

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(m_GLFWwindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	else
		LOG_ENGINE_WARN("GLFW: RAW_MOUSE_MOTION is not supported on this machine...");

	return true;
}

bool InputHandler::IsKeyPressed(u16 key)
{
	// Mouse key
	if (key >= Rutan::IO::Mouse::FIRST && key <= Rutan::IO::Mouse::LAST)
		return glfwGetMouseButton(m_GLFWwindow, key) == GLFW_PRESS;

	// Keyboard
	else if (key >= Rutan::IO::Keyboard::FIRST && key <= Rutan::IO::Keyboard::LAST)
		return glfwGetKey(m_GLFWwindow, key) == GLFW_PRESS;

	// Gamepad or Joystick for now...
	else
		return false;
}

void InputHandler::EnableCursor()
{
	if (!m_CursorEnabled) 
	{
		glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_CursorEnabled = true;
	}
}

void InputHandler::DisableCursor()
{
	if (m_CursorEnabled)
	{
		glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		m_CursorEnabled = false;

		// Center the mouse position
		CenterCursor();
	}
}

glm::dvec2 InputHandler::CenterCursor() const
{
	glm::ivec2 windowSize;
	glfwGetWindowSize(m_GLFWwindow, &windowSize.x, &windowSize.y);
	glm::dvec2 centerPos(windowSize.x / 2.0, windowSize.y / 2.0);
	glfwSetCursorPos(m_GLFWwindow, centerPos.x, centerPos.y);
	return centerPos;
}

glm::dvec2 InputHandler::GetMousePosition() const
{
	glm::dvec2 pos;
	glfwGetCursorPos(m_GLFWwindow, &pos.x, &pos.y);
	return glm::vec2(pos.x, pos.y);
}

glm::dvec2 InputHandler::GetMouseDelta() const
{
	glm::dvec2 mousePos = GetMousePosition();
	
	// Center the mouse position
	glm::dvec2 centerPos = CenterCursor();

	glm::dvec2 delta = (centerPos - mousePos) * static_cast<double>(m_MouseSensitivity);

	return delta;
}

//bool InputHandler::IsKeyReleased(u16 key)
//{
//	return glfwGetKey(m_GLFWwindow, key) == GLFW_RELEASE;
//}


}