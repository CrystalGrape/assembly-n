#include "VirtualMachine.h"
#include "ExternalCall.h"
///�����뺯��
void VirtualMachine::do_move(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("mov");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "movָ���һ�����������ǼĴ���");
	unsigned int opdata;
	switch (args[1].Type)
	{
	case OT_ImmediateData:
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
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "strָ���һ�����������ǼĴ���");
	unsigned int memoryAddr;
	switch (args[1].Type)
	{
	case OT_ImmediateData:
	case OT_DataPointer:
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
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "ldrָ���һ�����������ǼĴ���");
	unsigned int memoryAddr;
	switch (args[1].Type)
	{
	case OT_ImmediateData:
	case OT_DataPointer:
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
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "ֻ�ܶԼĴ�������ѹջ����");
	unsigned int opdata = Get(args[0].Data);
	Set(sp++, opdata);
}

void VirtualMachine::do_pop(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("pop");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "ֻ�ܶԼĴ���������ջ����");
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
	case OT_ImmediateData:
	case OT_DataPointer:
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
	case OT_ImmediateData:
	case OT_DataPointer:
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
	case OT_ImmediateData:
	case OT_DataPointer:
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
	throw VMExpection(EC_Exit);
}

void VirtualMachine::do_add(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("add");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "addָ���һ�����������ǼĴ���");
	if (args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "addָ��ڶ������������ǼĴ���");
	if (args[2].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "addָ����������������ǼĴ���");

	unsigned int opdata1 = Get(args[1].Data);
	unsigned int opdata2 = Get(args[2].Data);
	Set(args[0].Data, opdata1 + opdata2);
}
void VirtualMachine::do_sub(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("sub");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "subָ���һ�����������ǼĴ���");
	if (args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "subָ��ڶ������������ǼĴ���");
	if (args[2].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "subָ����������������ǼĴ���");

	unsigned int opdata1 = Get(args[1].Data);
	unsigned int opdata2 = Get(args[2].Data);
	Set(args[0].Data, opdata1 - opdata2);
}
void VirtualMachine::do_mul(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("mul");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "mulָ���һ�����������ǼĴ���");
	if (args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "mulָ��ڶ������������ǼĴ���");
	if (args[2].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "mulָ����������������ǼĴ���");

	unsigned int opdata1 = Get(args[1].Data);
	unsigned int opdata2 = Get(args[2].Data);
	Set(args[0].Data, opdata1 * opdata2);
}

void VirtualMachine::do_gt(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("gt");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "gtָ���һ�����������ǼĴ���");
	if (args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "gtָ��ڶ������������ǼĴ���");
	unsigned int opdata1 = Get(args[0].Data);
	unsigned int opdata2 = Get(args[1].Data);
	if (opdata1 > opdata2){
		cpsr |= 0x00000001;
	}
	else{
		cpsr &= 0xfffffffe;
	}
}
void VirtualMachine::do_gte(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("gte");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "gteָ���һ�����������ǼĴ���");
	if (args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "gteָ��ڶ������������ǼĴ���");
	unsigned int opdata1 = Get(args[0].Data);
	unsigned int opdata2 = Get(args[1].Data);
	if (opdata1 >= opdata2){
		cpsr |= 0x00000001;
	}
	else{
		cpsr &= 0xfffffffe;
	}
}
void VirtualMachine::do_lt(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("lt");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "ltָ���һ�����������ǼĴ���");
	if (args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "ltָ��ڶ������������ǼĴ���");
	unsigned int opdata1 = Get(args[0].Data);
	unsigned int opdata2 = Get(args[1].Data);
	if (opdata1 < opdata2){
		cpsr |= 0x00000001;
	}
	else{
		cpsr &= 0xfffffffe;
	}
}

void VirtualMachine::do_lte(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("lte");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "lteָ���һ�����������ǼĴ���");
	if (args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "lteָ��ڶ������������ǼĴ���");
	unsigned int opdata1 = Get(args[0].Data);
	unsigned int opdata2 = Get(args[1].Data);
	if (opdata1 <= opdata2){
		cpsr |= 0x00000001;
	}
	else{
		cpsr &= 0xfffffffe;
	}
}

void VirtualMachine::do_entry(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("entry");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "entryָ���һ�����������ǼĴ���");
	ExternalCall *ec = ExternalCall::GetInstance();
	Int32 Addr=Get(args[0].Data);
	ec->EntrySection((char *)this->GetPhysicalAddr(Addr));
}
void VirtualMachine::do_call(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("call");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "callָ���һ�����������ǼĴ���");
	ExternalCall *ec = ExternalCall::GetInstance();
	Int32 Addr = Get(args[0].Data);
	ec->CallFunction((char *)this->GetPhysicalAddr(Addr));
}
void VirtualMachine::do_exit(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("exit");
#endif
	ExternalCall *ec = ExternalCall::GetInstance();
	ec->ExitSection();
}

void VirtualMachine::do_strb(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("strb");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "strbָ���һ�����������ǼĴ���");
	if (args[1].Type != OT_DataPointer&&args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "strbָ��ڶ������������ǵ�ַ��Ĵ���");
	if (args[2].Type != OT_ImmediateData&&args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "strbָ�������������������������Ĵ���");
	unsigned int Data = Get(args[0].Data);
	unsigned int odata = Get(args[1].Data);
	unsigned int tmp;
	if (args[2].Type == OT_ImmediateData) {
		tmp = ~(0xff << (args[2].Data * 8));
		odata &= tmp;
		Data = Data << (args[2].Data * 8);
		odata |= Data;
	}
	else {
		tmp = ~(0xff << (Get(args[2].Data) * 8));
		odata &= tmp;
		Data = Data << (Get(args[2].Data) * 8);
		odata |= Data;
	}
	Set(args[1].Data, odata);
}

void VirtualMachine::do_ldrb(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("ldrb");
#endif
	if (args[0].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "strbָ���һ�����������ǼĴ���");
	if (args[1].Type != OT_DataPointer&&args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "strbָ��ڶ������������ǵ�ַ��Ĵ���");
	if (args[2].Type != OT_ImmediateData&&args[1].Type != OT_Register)
		throw VMExpection(EC_ArgsError, "strbָ�������������������������Ĵ���");
	unsigned int odata = Get(args[1].Data);
	unsigned int tmp;
	unsigned int Data;
	if (args[2].Type == OT_ImmediateData) {
		tmp = 0xff << (args[2].Data * 8);
		odata &= tmp;
		Data = odata >> (args[2].Data * 8);
	}
	else {
		tmp = 0xff << (Get(args[2].Data) * 8);
		odata &= tmp;
		Data = odata >> (Get(args[2].Data) * 8);
	}
	Set(args[0].Data, Data);
}

//���ж�ָ��
void VirtualMachine::do_swi(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("swi");
#endif
	lr = pc;
	sino = args[0].Data;
	pc = 1;		
	SetRunMode(RMC_Supervisor);
}

//�л�����ģʽ
void VirtualMachine::do_swm(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("swm");
#endif
	if (args[0].Data > 2 || args[0].Data < 0)
		throw VMExpection(EC_ArgsError, "swmָ���һ������������0-3֮��");
	SetRunMode(RunModCode(args[0].Data));
}
