#include "ExternalCall.h"

VirtualMachine *vm;
void push(Int32 OpData)
{
	vm->pushData(OpData);
}

Int32 pop()
{
	return vm->popData();
}

void *GetPhysicalAddr(Int32 Addr)
{
	return (void *)vm->GetPhysicalAddr(Addr);
}

void ExternalCall::SetRunTime(VirtualMachine *v)
{
	vm = v;
	runTime = new RunTime();
	runTime->pop = pop;
	runTime->push = push;
	runTime->GetPhysicalAddr = GetPhysicalAddr;
}

void ExternalCall::EntrySection(std::string dllName)
{
	hDllLib = LoadLibrary(dllName.data());
	if (!hDllLib)
		throw VMExpection(ExpectionCode::EntryExternalError);
}

void ExternalCall::CallFunction(std::string funcName)
{
	FARPROC fpFun = GetProcAddress(hDllLib, funcName.data());
	((AssemblyNFunc)fpFun)(this->runTime);
}

void ExternalCall::ExitSection()
{
	FreeLibrary(hDllLib);
}
