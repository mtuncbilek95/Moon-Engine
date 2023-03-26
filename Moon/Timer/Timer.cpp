#include "Timer.h"

#include <Moon/Window/WindowCore.h>

namespace Moon
{
	Timer* Timer::m_Timer = nullptr;

	Timer::Timer()
		: m_SecondsPerCount(0.0), m_DeltaTime(-1.0), m_StopTime(0), m_BaseTime(0),
		m_PausedTime(0), m_PrevTime(0), m_CurrTime(0), m_Stopped(false)
	{
		unsigned long long countsPerSec{};
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		m_SecondsPerCount = 1.0 / (double)countsPerSec;
	}

	float Timer::TotalTime()const
	{
		if (m_Stopped)
		{
			return (float)(((m_StopTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
		}

		else
		{
			return (float)(((m_CurrTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
		}
	}

	float Timer::DeltaTime()const
	{
		return (float)m_DeltaTime;
	}

	void Timer::Reset()
	{
		unsigned long long currTime{};
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_BaseTime = currTime;
		m_PrevTime = currTime;
		m_StopTime = 0;
		m_Stopped = false;
	}

	void Timer::Start()
	{
		unsigned long long startTime{};
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

		if (m_Stopped)
		{
			m_PausedTime += (startTime - m_StopTime);

			m_PrevTime = startTime;
			m_StopTime = 0;
			m_Stopped = false;
		}
	}

	void Timer::Stop()
	{
		if (!m_Stopped)
		{
			unsigned long long currTime{};
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

			m_StopTime = currTime;
			m_Stopped = true;
		}
	}

	void Timer::Tick()
	{
		if (m_Stopped)
		{
			m_DeltaTime = 0.0;
			return;
		}

		unsigned long long currTime{};
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		m_CurrTime = currTime;

		m_DeltaTime = (m_CurrTime - m_PrevTime) * m_SecondsPerCount;

		m_PrevTime = m_CurrTime;

		if (m_DeltaTime < 0.0)
		{
			m_DeltaTime = 0.0;
		}
	}
}