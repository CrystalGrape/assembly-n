#pragma once
#include "ErrorDefine.h"
enum MemoryAttribute
{
	MA_READONLY,
	MA_READWRITE
};

class MemoryManager
{
public:
	MemoryManager();
	~MemoryManager();
	MemoryManager(unsigned int MemorySize);
	unsigned int Get(unsigned int Addr);
	void Set(unsigned int Addr, unsigned int Value);
	unsigned int *GetPhysicalAddr(unsigned int Addr);
private:
	unsigned int *Memory;
	MemoryAttribute *MemoryInfo;
	unsigned int MemorySize;
};

