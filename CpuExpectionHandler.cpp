#include "VirtualMachine.h"

//判断当前模式下是否可以运行指令
bool VirtualMachine::AllowRun(OpCode code)
{
	RunModCode mode = CurrentRunMode();
	return RunModePower::Instance().AllowRun(mode, code);
}

//获取当前运行模式
RunModCode VirtualMachine::CurrentRunMode()
{
	int mode = (cpsr & 0x00000110) >> 1;
	return RunModCode(mode);
}