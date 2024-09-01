#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace Rutan::Core { class Window; }

namespace Rutan::Graphics
{


class Renderer
{
public:
	// Common interface
	virtual bool Init(const Rutan::Core::Window& window) = 0;

	virtual void OnResize(const glm::uvec2& resolution) = 0;

	virtual void ClearScreen(const glm::vec4& color) = 0;	//SetClearColor
	virtual void Render() = 0;
};


}
