#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(int MaxMemorySize)
{
	for (int i = 0; i < 13; i++) {
		R[i] = 0x00000000;
	}
	Memory = MemoryManager(MaxMemorySize);
}

unsigned int VirtualMachine::Get(unsigned int Addr)
{
	if (Addr > RegisterMaxAddr) {
		throw VMExpection(ExpectionCode::OutOfMemory, Addr);
	}

	if (Addr >= RegisterBaseAddr) {
		return R[Addr - RegisterBaseAddr];
	}
	else {
		return Memory.Get(Addr);
	}
}

void VirtualMachine::Set(unsigned int Addr, unsigned int Value)
{
	if (Addr > RegisterMaxAddr) {
		throw VMExpection(ExpectionCode::OutOfMemory, Addr);
	}

	if (Addr >= RegisterBaseAddr) {
		R[Addr - RegisterBaseAddr] = Value;
	}
	else {
		Memory.Set(Addr, Value);
	}
}
