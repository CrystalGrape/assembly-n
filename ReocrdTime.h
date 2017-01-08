#pragma once
#include <time.h>
#include <iostream>
#include <windows.h>
#define RECORDTIME
class RecordTime
{
public:
	RecordTime(std::string OpCode)
	{
		/*startTime = clock();*/
		this->OpCode = OpCode;
		QueryPerformanceFrequency(&freq_);
		QueryPerformanceCounter(&begin_time);
	}
	~RecordTime()
	{
		QueryPerformanceCounter(&end_time);
		std::cout << OpCode.data() 
			<< ":" 
			<< (end_time.QuadPart - begin_time.QuadPart) * 1000000.0 / freq_.QuadPart << "us" 
			<< std::endl;
		/*endTime = clock();
		std::cout << OpCode.data() << ":" << endTime - startTime << "ms" << std::endl;*/
	}
private:
	/*clock_t startTime, endTime;*/
	std::string OpCode;
	LARGE_INTEGER freq_;
	LARGE_INTEGER begin_time;
	LARGE_INTEGER end_time;
};