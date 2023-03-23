#pragma once

#include <Moon/Core/MoonCore.h>

namespace Moon
{
	class FileSystem
	{
	public:
		static FileSystem& GetInstance();

		void SetProjectTarget(string p_TargetDir);
		string GetGameDir();
		string GetData(string p_PathName);

	private:
		string m_GameTargetDir;

	private:
		static FileSystem* m_FileSystem;
	};
}