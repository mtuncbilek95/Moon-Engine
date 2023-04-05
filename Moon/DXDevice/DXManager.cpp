#include "DXManager.h"

namespace Moon
{
	DXModule* DXManager::m_DXModule = nullptr;

	DXModule& DXManager::GetInstance()
	{
		if (!m_DXModule)
			m_DXModule = new DXModule();
		return *m_DXModule;
	}
}