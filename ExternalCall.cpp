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
#if WINDOWS
	hDllLib = LoadLibrary(dllName.data());
#elif LINUX
	hDllLib = dlopen(path, RTLD_LAZY);
#endif
	if (!hDllLib)
		throw VMExpection(EC_EntryExternalError);
}

void ExternalCall::CallFunction(std::string funcName)
{
#if WINDOWS
	FARPROC fpFun = GetProcAddress(hDllLib, funcName.data());
	((AssemblyNFunc)fpFun)(this->runTime);
#elif LINUX
	AssemblyNFunc fpFun = (AssemblyNFunc)dlsym(hDllLib, funcName.data());
	fpFun(this->runTime);
#endif
	
}

void ExternalCall::ExitSection()
{
#if WINDOWS
	FreeLibrary(hDllLib);
#elif LINUX
	dlclose(hDllLib);
#endif
}
