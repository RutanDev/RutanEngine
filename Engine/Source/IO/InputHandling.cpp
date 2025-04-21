#include "EnginePCH.h"
#include <IO/InputHandling.h>
#include <IO/Keycodes.h>
#include <GLFW/glfw3.h>

namespace Rutan::IO
{


InputHandler::InputHandler()
	: m_GLFWwindow(nullptr)
{
}

InputHandler::~InputHandler()
{
}

bool InputHandler::Init(GLFWwindow* windowHandle)
{
	m_GLFWwindow = windowHandle;
	return true;
}

bool InputHandler::IsKeyPressed(u16 key)
{
	return glfwGetKey(m_GLFWwindow, key) == GLFW_PRESS;
}

//bool InputHandler::IsKeyReleased(u16 key)
//{
//	return glfwGetKey(m_GLFWwindow, key) == GLFW_RELEASE;
//}


}