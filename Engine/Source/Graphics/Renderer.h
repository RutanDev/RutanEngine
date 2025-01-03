#pragma once
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace Rutan::Core { class Window; }
namespace std::filesystem { class path; }

namespace Rutan::Graphics
{


class Renderer
{
public:
	// Common interface
	virtual bool Init(const Rutan::Core::Window& window, const std::filesystem::path& shadersPath) = 0;
	virtual void OnResize(const glm::uvec2& resolution) = 0;
	virtual void SetClearColor(const glm::vec4& color) = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

};


}
