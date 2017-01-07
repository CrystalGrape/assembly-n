#include "VirtualMachine.h"
///�����뺯��
void VirtualMachine::do_move(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("mov");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "movָ���һ�����������ǼĴ���");
	unsigned int opdata;
	switch (args[1].Type)
	{
	case OpDataType::ImmediateData:
		opdata = args[1].Data;
		break;
	default:
		opdata = Get(args[1].Data);
		break;
	}
	Set(args[0].Data, opdata);
}
void VirtualMachine::do_str(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("str");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "strָ���һ�����������ǼĴ���");
	unsigned int memoryAddr;
	switch (args[1].Type)
	{
	case OpDataType::ImmediateData:
	case OpDataType::DataPointer:
		memoryAddr = args[1].Data;
		break;
	default:
		memoryAddr = Get(args[1].Data);
		break;
	}
	Set(memoryAddr, Get(args[0].Data));
}
void VirtualMachine::do_ldr(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("ldr");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "ldrָ���һ�����������ǼĴ���");
	unsigned int memoryAddr;
	switch (args[1].Type)
	{
	case OpDataType::ImmediateData:
	case OpDataType::DataPointer:
		memoryAddr = args[1].Data;
		break;
	default:
		memoryAddr = Get(args[1].Data);
		break;
	}
	Set(args[0].Data, Get(memoryAddr));
}
void VirtualMachine::do_push(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("push");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "ֻ�ܶԼĴ�������ѹջ����");
	unsigned int opdata = Get(args[0].Data);
	Set(sp++, opdata);
}
void VirtualMachine::do_pop(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("pop");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "ֻ�ܶԼĴ���������ջ����");
	Set(args[0].Data, Get(--sp));
}
void VirtualMachine::do_jmp(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("jmp");
#endif
	unsigned int pcAddr;
	switch (args[0].Type)
	{
	case OpDataType::ImmediateData:
	case OpDataType::DataPointer:
		pcAddr = args[0].Data;
		break;
	default:
		pcAddr = Get(args[0].Data);
		break;
	}
	pc = pcAddr;
}

void VirtualMachine::do_cjmp(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("cjmp");
#endif
	if ((cpsr & 0x00000001) == 0)
		return;
	unsigned int pcAddr;
	switch (args[0].Type)
	{
	case OpDataType::ImmediateData:
	case OpDataType::DataPointer:
		pcAddr = args[0].Data;
		break;
	default:
		pcAddr = Get(args[0].Data);
		break;
	}
	pc = pcAddr;
	cpsr &= 0xfffffffe;
}

void VirtualMachine::do_bjmp(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("bjmp");
#endif
	lr = pc;
	unsigned int pcAddr;
	switch (args[0].Type)
	{
	case OpDataType::ImmediateData:
	case OpDataType::DataPointer:
		pcAddr = args[0].Data;
		break;
	default:
		pcAddr = Get(args[0].Data);
		break;
	}
	pc = pcAddr;
}

void VirtualMachine::do_ret(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("ret");
#endif
	pc = lr;
}

void VirtualMachine::do_end(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("end");
#endif
	throw VMExpection(Exit);
}