#pragma once

#include <Core/MoonCore.h>

namespace Moon {

	class FileSystem {
	public:
		static FileSystem& GetInstance();

		void SetProjectTarget(string p_TargetDir);

		string GetCurrentDir();

		string GetData(string p_PathName);
	private:
		string m_TargetDir;
	private:
		static FileSystem* m_FileSystem;
	};
}