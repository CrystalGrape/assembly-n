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
	int mode = (cpsr & 0x00000110) >> 1;
	return RunModCode(mode);
}