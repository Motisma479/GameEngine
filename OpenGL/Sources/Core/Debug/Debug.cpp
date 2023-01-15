#include "Core/Debug/Debug.hpp"

#include <time.h>
#include <filesystem>

Debug::Log::Log() 
{
	time_t temp;
	struct tm datetime;
	char  format[32];
	time(&temp);
	localtime_s(&datetime ,&temp);
	strftime(format, 32, "%Y_%m_%d", &datetime);
	std::filesystem::create_directory("Log");
	fileName = "Log/";
	fileName += format;
	fileName += ".log";
	logFile.open(fileName, std::ios_base::out);
	ASSERT(logFile.is_open());
}

bool is_empty(std::fstream& p_file)
{
	return p_file.peek() == std::fstream::traits_type::eof();
}
Debug::Log::~Log()
{
	if (is_empty(logFile))
	{
		logFile.close();
		std::remove(fileName.c_str());
	}
	else
	{
		logFile.close();
	}
}


void Debug::Log::Print(const char* p_message)
{
	logFile << p_message << std::endl;
}