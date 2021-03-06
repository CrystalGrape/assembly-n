#include "MemoryManager.h"

MemoryManager::MemoryManager()
{
}

MemoryManager::~MemoryManager()
{
	delete[] Memory;
	delete[] MemoryInfo;
}

MemoryManager::MemoryManager(unsigned int MemorySize)
{
	this->MemorySize = MemorySize;
	Memory = new unsigned int[MemorySize / 4];
	MemoryInfo = new MemoryAttribute[MemorySize / 4];
	for (int i = 0; i < (int)MemorySize / 4; i++) {
		MemoryInfo[i] = MA_READWRITE;
	}
}

unsigned int MemoryManager::Get(unsigned int Addr)
{
	if (Addr >= MemorySize / 4 || Addr < 0)
		throw VMExpection(EC_OutOfMemory, Addr);
	return *(Memory + Addr);
}

void MemoryManager::Set(unsigned int Addr, unsigned int Value)
{
	if (Addr >= MemorySize / 4 || Addr < 0)
		throw VMExpection(EC_OutOfMemory, Addr);
	if (MemoryInfo[Addr] == MA_READONLY)
		throw VMExpection(EC_ReadOnly, Addr);
	*(Memory + Addr) = Value;
}

unsigned int *MemoryManager::GetPhysicalAddr(unsigned int Addr)
{
	return (Memory + Addr);
}

