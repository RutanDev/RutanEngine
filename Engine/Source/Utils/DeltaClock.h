#pragma once
#include <chrono>

namespace Rutan
{

	
class DeltaClock
{
public:
	DeltaClock();
	~DeltaClock() = default;

	f64 GetSeconds();
	f64 GetMilliseconds();
	f64 GetMicroseconds();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_LastTime;

};


}
