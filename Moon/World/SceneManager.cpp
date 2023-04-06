#include "SceneManager.h"

namespace Moon
{
	SceneModule* SceneManager::m_SceneModule = nullptr;

	SceneModule& SceneManager::GetInstance()
	{
		if (!m_SceneModule)
			m_SceneModule = new SceneModule();
		return *m_SceneModule;
	}
}