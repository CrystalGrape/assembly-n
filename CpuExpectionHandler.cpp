#include "VirtualMachine.h"

//�жϵ�ǰģʽ���Ƿ��������ָ��
bool VirtualMachine::AllowRun(OpCode code)
{
	RunModCode mode = CurrentRunMode();
	return RunModePower::Instance().AllowRun(mode, code);
}

//��ȡ��ǰ����ģʽ
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
