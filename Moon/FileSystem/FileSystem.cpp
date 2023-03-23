#include "FileSystem.h"

#include <Moon/Window/WindowCore.h>

namespace Moon
{
	FileSystem* FileSystem::m_FileSystem = nullptr;

	FileSystem& FileSystem::GetInstance()
	{
		if (m_FileSystem == nullptr)
			m_FileSystem = new FileSystem();
		return *m_FileSystem;
	}

	void FileSystem::SetProjectTarget(string p_TargetDir)
	{
		m_GameTargetDir = p_TargetDir;
	}

	void FileSystem::SetEngineSourceTarget(string p_TargetDir)
	{

	}

	string FileSystem::GetGameDir()
	{
		return m_GameTargetDir;
	}

	string FileSystem::GetData(string p_PathName)
	{
		string fullPath = GetGameDir() + p_PathName;

		HANDLE fileHandle;

		bool bIsFileOk;
		DWORD countByte;

		fileHandle = CreateFileA(fullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS,
			FILE_ATTRIBUTE_READONLY, nullptr);

		const DWORD fileSize = GetFileSize(fileHandle, nullptr);

		char* stringFile = new char[fileSize + 1];
		stringFile[fileSize] = { '\0' };

		try
		{
			if (bIsFileOk = ReadFile(fileHandle, stringFile, fileSize, &countByte, nullptr))
			{
				return string(stringFile);
			}
			else
			{
				throw "Unexpected file or path.";
			}
		}
		catch (const string exception)
		{
			printf("Error: %s", (char*)&exception);
			return nullptr;
		}
	}
}