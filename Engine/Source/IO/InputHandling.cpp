#include "EnginePCH.h"
#include <IO/InputHandling.h>
#include <IO/Keycodes.h>
#include <GLFW/glfw3.h>

namespace Rutan::IO
{


InputHandler::InputHandler()
	: m_GLFWwindow(nullptr)
	, m_InputStatus()
{
}

InputHandler::~InputHandler()
{
}

bool InputHandler::Init(GLFWwindow* windowHandle)
{
	if (!windowHandle) 
	{
		LOG_ENGINE_FATAL("Input: GLFW window was nullptr...");
		return false;
	}

	m_GLFWwindow = windowHandle;

	glfwSetWindowUserPointer(m_GLFWwindow, this);

	glfwSetKeyCallback(m_GLFWwindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_UNKNOWN) return;
		
		InputHandler* input = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
		input->m_InputStatus[key] = action + 1;
		input->m_InputQueue.push(key);
	});

	glfwSetMouseButtonCallback(m_GLFWwindow, [](GLFWwindow* window, int button, int action, int mods)
	{
		if (button == GLFW_KEY_UNKNOWN) return;

		// TODO: Action: Pressed and released
		InputHandler* input = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
		input->m_InputStatus[button] = action + 1;
		input->m_InputQueue.push(button);
	});

	return true;
}

bool InputHandler::IsKeyPressed(u16 key)
{
	return m_InputStatus[key] == GLFW_PRESS + 1;
}

bool InputHandler::IsKeyHeld(u16 key)
{
	return m_InputStatus[key] == GLFW_REPEAT + 1;
}

bool InputHandler::IsKeyReleased(u16 key)
{
	return m_InputStatus[key] == GLFW_RELEASE + 1;
}

void InputHandler::ClearInputStatus()
{
	// Reseting all the buttons that was pressed/held/released for this frame
	while (!m_InputQueue.empty())
	{
		u16 key = m_InputQueue.front();
		m_InputQueue.pop();
		m_InputStatus[key] = 0;
	}
}


}