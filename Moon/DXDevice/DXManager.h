#pragma once

#include <Moon/DXDevice/DXModule.h>

namespace Moon
{
	class DXManager
	{
	public:
		static DXModule& GetInstance();

	private:
		static DXModule* m_DXModule;
	};
}