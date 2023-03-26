#pragma once

#include <Moon/Core/MoonCore.h>

namespace Moon
{
	class Timer
	{
	public:
		static Timer& GetInstance()
		{
			if (m_Timer == nullptr)
				m_Timer = new Timer();
			return *m_Timer;
		}

		float TotalTime() const;
		float DeltaTime() const;

		void Reset();
		void Start();
		void Stop();
		void Tick();

	private:
		Timer();

		double m_SecondsPerCount;
		double m_DeltaTime;

		unsigned long long m_BaseTime;
		unsigned long long m_PausedTime;
		unsigned long long m_StopTime;
		unsigned long long m_PrevTime;
		unsigned long long m_CurrTime;

		bool m_Stopped;

	private:
		static Timer* m_Timer;
	};
}