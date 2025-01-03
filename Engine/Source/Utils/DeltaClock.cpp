#include "EnginePCH.h"
#include "DeltaClock.h"


namespace Rutan
{


DeltaClock::DeltaClock()
{
	m_LastTime = std::chrono::high_resolution_clock::now();
}

f64 DeltaClock::GetSeconds()
{
	const auto& endtime = std::chrono::high_resolution_clock::now();
	f64 timePast = std::chrono::duration<f64>(endtime - m_LastTime).count();
	m_LastTime = endtime;
	return timePast;
}

f64 DeltaClock::GetMilliseconds()
{
	const auto& endtime = std::chrono::high_resolution_clock::now();
	f64 timePast = std::chrono::duration<f64, std::milli>(endtime - m_LastTime).count();
	m_LastTime = endtime;
	return timePast;
}

f64 DeltaClock::GetMicroseconds()
{
	const auto& endtime = std::chrono::high_resolution_clock::now();
	f64 timePast = std::chrono::duration<f64, std::micro>(endtime - m_LastTime).count();
	m_LastTime = endtime;
	return timePast;
}


}
