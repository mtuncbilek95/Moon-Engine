#pragma once

#include <Moon/World/SceneModule.h>

namespace Moon
{
	class SceneManager
	{
	public:
		static SceneModule& GetInstance();
	private:
		static SceneModule* m_SceneModule;
	};
}