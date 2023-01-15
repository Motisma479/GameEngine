#pragma once

#include<cassert>
#include<fstream>
#include <iostream>
#include <cstdarg>

#ifdef _DEBUG
#define ASSERT(cond) assert((cond));			//inDebug
#else
#define ASSERT(cond) if(!(cond)) {exit(-1);}		//inRealise
#endif
#define DEBUG_LOG(...)	std::cout<< __FILE__ << "(" << __LINE__ << "):";printf(__VA_ARGS__);
//std::cout<< __FILE__ << "(" << __LINE__ << "):" << (text) << std::endl;






namespace Debug 
{
	class Log
	{
	private:
		std::fstream logFile;
		std::string fileName;
	public:
		//Constructor
		Log();
		//Destructor
		~Log();
		//function
		void Print(const char* p_message);
	};
}