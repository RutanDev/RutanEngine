#include "EnginePCH.h"
#include <IO/InputHandling.h>
#include <IO/Keycodes.h>

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
	m_GLFWwindow = windowHandle;
	return true;
}

void InputHandler::SetKeyStatus(u16 key, u8 status)
{
	m_InputStatus[key] = status + 1; // Need an offset
	m_InputQueue.push(key);
}

bool InputHandler::IsKeyPressed(u16 key)
{
	return m_InputStatus[key] == KeyStatus::Press;
}

bool InputHandler::IsKeyHeld(u16 key)
{
	return m_InputStatus[key] == KeyStatus::Repeat;
}

bool InputHandler::IsKeyReleased(u16 key)
{
	return m_InputStatus[key] == KeyStatus::Release;
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