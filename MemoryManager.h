#pragma once
#include "ErrorDefine.h"
enum MemoryAttribute
{
	READONLY,
	READWRITE
};

class MemoryManager
{
public:
	MemoryManager();
	MemoryManager(unsigned int MemorySize);
	unsigned int Get(unsigned int Addr);
	void Set(unsigned int Addr, unsigned int Value);
private:
	unsigned int *Memory;
	MemoryAttribute *MemoryInfo;
	unsigned int MemorySize;
};

