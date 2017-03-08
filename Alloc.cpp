#include "Alloc.h"

Alloc::Alloc(int StartAddr, int MemorySize)
{
	this->IdentifyIncrease = 1;
	this->StartAddr = StartAddr;
	this->MemorySize = MemorySize / 4;

	for (int i = this->StartAddr; i < this->MemorySize; i++)
	{
		FreeMemory.push_back(MemoryIdentify(i, 0));
		FreeMemory.push_back(MemoryIdentify(i, 1));
		FreeMemory.push_back(MemoryIdentify(i, 2));
		FreeMemory.push_back(MemoryIdentify(i, 3));
	}
}

MemoryIdentify Alloc::Malloc(size_t size)
{
	int Index = FindContinuityAddr(size);
	for (int i = Index; i < Index + (int)size; i++)
	{
		FreeMemory[i].Identify = IdentifyIncrease;
	}
	IdentifyIncrease++;
	return FreeMemory[Index];
}

void Alloc::Free(MemoryIdentify Identify)
{
	int Index = (Identify.BaseAddr - StartAddr) * 4 + Identify.Offset;
	int MemId = FreeMemory[Index].Identify;
	for (int i = Index; FreeMemory[i].Identify == MemId; i++)
	{
		FreeMemory[i].Identify = 0;
	}
}

int Alloc::FindContinuityAddr(size_t size)
{
	for (int i = 0; i < (int)FreeMemory.size() - 1; i++)
	{
		bool flag = true;
		for (int j = i; j < (int)size + i; j++)
		{
			if (!FreeMemory[j].IsContinuity(FreeMemory[j + 1])) {
				flag = false;
				break;
			}
		}
		if (flag)
			return i;
	}
	
	throw VMExpection(EC_AllocMemroyFailed, size);
}

//内存标识符实现
MemoryIdentify::MemoryIdentify(unsigned int BaseAddr, unsigned int Offset, unsigned int Identify)
{
	this->BaseAddr = BaseAddr;
	this->Offset = Offset;
	this->Identify = Identify;
}

bool MemoryIdentify::IsContinuity(MemoryIdentify next)
{
	if (this->Identify == 0 && next.Identify == 0)
		return true;
	return false;
}

bool operator<(const MemoryIdentify & a, const MemoryIdentify & b)
{
	if (a.BaseAddr < b.BaseAddr)
		return true;
	if (a.BaseAddr == b.BaseAddr&&a.Offset < b.Offset)
		return true;
	return false;
}



