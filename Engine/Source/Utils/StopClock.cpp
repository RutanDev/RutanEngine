#include "EnginePCH.h"
#include "StopClock.h"


namespace Rutan
{


StopClock::StopClock()
{
	m_IsRunning = false;
}

void StopClock::Start()
{
	m_IsRunning = true;
	m_StartTime = std::chrono::high_resolution_clock::now();
}

void StopClock::Stop()
{
	m_IsRunning = false;
	m_EndTime = std::chrono::high_resolution_clock::now();
}

f64 StopClock::GetSeconds()
{
	const auto endtime = m_IsRunning ? std::chrono::high_resolution_clock::now() : m_EndTime;
	return std::chrono::duration<f64>(endtime - m_StartTime).count();
}

f64 StopClock::GetMilliseconds()
{
	const auto endtime = m_IsRunning ? std::chrono::high_resolution_clock::now() : m_EndTime;
	return std::chrono::duration<f64, std::milli>(endtime - m_StartTime).count();
}

f64 StopClock::GetMicroseconds()
{
	const auto endtime = m_IsRunning ? std::chrono::high_resolution_clock::now() : m_EndTime;
	return std::chrono::duration<f64, std::micro>(endtime - m_StartTime).count();
}


}
