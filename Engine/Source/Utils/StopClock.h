#pragma once
#include <chrono>

namespace Rutan
{

	
class StopClock
{
public:
	StopClock();
	~StopClock() = default;

	void Start();
	void Stop();
	f64 GetSeconds();
	f64 GetMilliseconds();
	f64 GetMicroseconds();

private:
	bool m_IsRunning;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTime;
};


}
