#include "Timer.hpp"

#include <math.h>

#include "Logger.hpp"

namespace BARE2D {

	Timer::Timer()
	{
		m_frameTime = 0.0;
	}

	bool Timer::integrateFrame()
	{
		if(m_frameTime > m_minDeltaTime) {
			m_frameTime -= std::min(m_frameTime, m_minDeltaTime);
			return true;
		} else {
			return false;
		}
	}

	double Timer::getDeltaTime()
	{
		return m_minDeltaTime > 1.0/100000.0 ? std::min(m_frameTime, m_minDeltaTime) : m_frameTime;
	}

	void Timer::startTimer()
	{
		m_startTime = std::chrono::steady_clock::now();
	}

	void Timer::endTimer()
	{
		std::chrono::steady_clock::time_point newTime = std::chrono::steady_clock::now();
		
		double deltaMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(newTime - m_startTime).count();
		
		// Convert from microseconds to fractional seconds.
		m_frameTime += deltaMicroseconds / 1000000.0;
	}

	void Timer::setDeltaTimeLimit(double minDt)
	{
		m_minDeltaTime = minDt;
	}

}
