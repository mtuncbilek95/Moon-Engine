#pragma once

#include <Moon/Core/MoonCore.h>

namespace Moon
{
	class GameTimer
	{
	public:
		GameTimer();

		float TotalTime() const;
		float DeltaTime() const;

		void Reset();
		void Start();
		void Stop();
		void Tick();

	private:
		double m_SecondsPerCount;
		double m_DeltaTime;

		unsigned long long m_BaseTime;
		unsigned long long m_PausedTime;
		unsigned long long m_StopTime;
		unsigned long long m_PrevTime;
		unsigned long long m_CurrTime;

		bool m_Stopped;
	};
}