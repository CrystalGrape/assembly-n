#pragma once
#include "MemoryManager.h"
typedef unsigned int Int32;
#define RegisterBaseAddr 0x56000000
#define RegisterMaxAddr 0x56000012
class VirtualMachine
{
public:
	VirtualMachine(int MaxMemorySize);
	~VirtualMachine();
	unsigned int Get(unsigned int Addr);
	void Set(unsigned int Addr, unsigned int Value);
private:
	//0x00000000-0x56000000
	MemoryManager Memory;
	//0x56000000ÒÔÉÏÊÇ¼Ä´æÆ÷
	/*
		R10=PC
		R11=LR
		R12=SP
	*/
	Int32 R[13];
};

