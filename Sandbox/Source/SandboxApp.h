#pragma once
#include <Core/Application.h>

class SandboxApp : public Rutan::Application
{
public:
	SandboxApp(const std::string& nameOfApp);
	~SandboxApp() = default;

	// Inherited via Application
	virtual void Init() override;
	virtual void Clean() override;
	virtual void Input() override;
	virtual void Update(f64 dt) override;
	virtual void Render() override;
	virtual void RenderGUI() override;
};
