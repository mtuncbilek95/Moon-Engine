#pragma once

#include <Moon/Core/MoonCore.h>

namespace Moon
{
#define RED			"\033[0;31m"
#define GREEN		"\033[0;32m"
#define YELLOW		"\033[0;33m"
#define BLUE		"\033[0;34m"
#define CYAN		"\033[0;36m"
#define WHITE		"\033[0;37m"

#define Moon_Success		"\033[0;32m[Success] -- "
#define Moon_Warning		"\033[0;33m[Warning] -- "
#define Moon_Error			"\033[0;31m[Error]   -- "
#define Moon_Info			"\033[0;36m[Info]    -- "
#define Moon_Display		"\033[0;37m[Display] -- "

	enum class LogType : byte
	{
		Display,
		Info,
		Success,
		Warning,
		Error
	};

	class Log
	{
	public:
		template<typename... TArgs>
		static void ConsoleLog(LogType p_Type = LogType::Display, TArgs... args)
		{

			string messageFinal{};

			switch (p_Type)
			{
			case LogType::Success:
				messageFinal += Moon_Success;
				break;
			case LogType::Warning:
				messageFinal += Moon_Warning;
				break;
			case LogType::Error:
				messageFinal += Moon_Error;
				break;
			case LogType::Display:
				messageFinal += Moon_Display;
				break;
			case LogType::Info:
				messageFinal += Moon_Info;
				break;
			default:
				messageFinal += WHITE;
				break;
			}

			std::cout << messageFinal << WHITE;
			(std::cout << ... << args) << std::endl;
		}
	};
}