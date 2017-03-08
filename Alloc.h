#pragma once
#include "ErrorDefine.h"
#include <vector>
class MemoryIdentify
{
public:
	unsigned int BaseAddr;
	unsigned int Offset;
	unsigned int Identify;
public:
	MemoryIdentify(unsigned int BaseAddr, unsigned int Offset, unsigned int Identify = 0);
	friend bool operator<(const MemoryIdentify& a, const MemoryIdentify& b);
	bool IsContinuity(MemoryIdentify next);
};
class Alloc
{
public:
	Alloc(int StartAddr, int MemorySize);
	MemoryIdentify Malloc(size_t size);
	void Free(MemoryIdentify Identify);
private:
	int StartAddr;
	int MemorySize;
	std::vector<MemoryIdentify> FreeMemory;
	unsigned int IdentifyIncrease;
private:
	int FindContinuityAddr(size_t size);
};

