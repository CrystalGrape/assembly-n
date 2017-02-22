#pragma once

#if WINDOWS
	#include <windows.h>
#elif LINUX
	#include <dlfcn.h>
#endif
#include <iostream>
#include "VirtualMachine.h"
#include "ErrorDefine.h"

struct RunTime
{
	void (*push)(Int32);
	Int32 (*pop)();
	void *(*GetPhysicalAddr)(Int32);
};

//外部调用类
class ExternalCall
{
public:
	static ExternalCall *GetInstance()
	{
		static ExternalCall *instance = new ExternalCall();
		return instance;
	}
	void SetRunTime(VirtualMachine *vm);
	void EntrySection(std::string dllName);
	void CallFunction(std::string funcName);
	void ExitSection();
private:
#if WINDOWS
	HMODULE hDllLib;
#elif LINUX
	void *hDllLib;
#endif
	RunTime *runTime;
	ExternalCall(){ runTime = NULL; };
	typedef void(*AssemblyNFunc)(RunTime *);
};

