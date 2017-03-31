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
	int mode = (cpsr & 0x00000006) >> 1;
	return RunModCode(mode);
}

void VirtualMachine::SetRunMode(RunModCode mode)
{
	cpsr &= (~0x00000006);
	unsigned int data = mode;
	data = data & 0x00000003;
	cpsr |= (data << 1);
}
