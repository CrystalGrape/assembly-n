#include "VirtualMachine.h"
#include "ExternalCall.h"
///操作码函数
void VirtualMachine::do_move(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("mov");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "mov指令第一个参数必须是寄存器");
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
		throw VMExpection(ArgsError, "str指令第一个参数必须是寄存器");
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
		throw VMExpection(ArgsError, "ldr指令第一个参数必须是寄存器");
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
		throw VMExpection(ArgsError, "只能对寄存器进行压栈操作");
	unsigned int opdata = Get(args[0].Data);
	Set(sp++, opdata);
}

void VirtualMachine::do_pop(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("pop");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "只能对寄存器进行退栈操作");
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

void VirtualMachine::do_add(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("add");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "add指令第一个参数必须是寄存器");
	if (args[1].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "add指令第二个参数必须是寄存器");
	if (args[2].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "add指令第三个参数必须是寄存器");

	unsigned int opdata1 = Get(args[1].Data);
	unsigned int opdata2 = Get(args[2].Data);
	Set(args[0].Data, opdata1 + opdata2);
}
void VirtualMachine::do_sub(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("sub");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "sub指令第一个参数必须是寄存器");
	if (args[1].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "sub指令第二个参数必须是寄存器");
	if (args[2].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "sub指令第三个参数必须是寄存器");

	unsigned int opdata1 = Get(args[1].Data);
	unsigned int opdata2 = Get(args[2].Data);
	Set(args[0].Data, opdata1 - opdata2);
}
void VirtualMachine::do_mul(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("mul");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "mul指令第一个参数必须是寄存器");
	if (args[1].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "mul指令第二个参数必须是寄存器");
	if (args[2].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "mul指令第三个参数必须是寄存器");

	unsigned int opdata1 = Get(args[1].Data);
	unsigned int opdata2 = Get(args[2].Data);
	Set(args[0].Data, opdata1 * opdata2);
}

void VirtualMachine::do_gt(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("gt");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "gt指令第一个参数必须是寄存器");
	if (args[1].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "gt指令第二个参数必须是寄存器");
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
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "gte指令第一个参数必须是寄存器");
	if (args[1].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "gte指令第二个参数必须是寄存器");
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
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "lt指令第一个参数必须是寄存器");
	if (args[1].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "lt指令第二个参数必须是寄存器");
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
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "lte指令第一个参数必须是寄存器");
	if (args[1].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "lte指令第二个参数必须是寄存器");
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
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "entry指令第一个参数必须是寄存器");
	ExternalCall *ec = ExternalCall::GetInstance();
	Int32 Addr=Get(args[0].Data);
	ec->EntrySection((char *)this->GetPhysicalAddr(Addr));
}
void VirtualMachine::do_call(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("call");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "entry指令第一个参数必须是寄存器");
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
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "strb指令第一个参数必须是寄存器");
	if (args[1].Type!=OpDataType::DataPointer)
		throw VMExpection(ArgsError, "strb指令第二个参数必须是地址");
	if (args[2].Type!=OpDataType::ImmediateData)
		throw VMExpection(ArgsError, "strb指令第三个参数必须是立即数");
	if (args[2].Data >= 4 || args[2].Data < 0)
		throw VMExpection(ArgsError, "strb指令第三个参数超过范围");
	unsigned int Data = Get(args[0].Data);
	unsigned int odata = Get(args[1].Data);
	unsigned int tmp = ~(0xff << (args[2].Data * 8));
	odata &= tmp;
	Data = Data << (args[2].Data * 8);
	odata |= Data;
	Set(args[1].Data, odata);
}
void VirtualMachine::do_ldrb(OpData args[3])
{
#ifdef RECORDTIME
	RecordTime time("ldrb");
#endif
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "strb指令第一个参数必须是寄存器");
	if (args[1].Type != OpDataType::DataPointer)
		throw VMExpection(ArgsError, "strb指令第二个参数必须是地址");
	if (args[2].Type != OpDataType::ImmediateData)
		throw VMExpection(ArgsError, "strb指令第三个参数必须是立即数");
	if (args[2].Data >= 4 || args[2].Data < 0)
		throw VMExpection(ArgsError, "strb指令第三个参数超过范围");
	unsigned int odata = Get(args[1].Data);
	unsigned int tmp = 0xff << (args[2].Data * 8);
	odata &= tmp;
	unsigned int Data = odata >> (args[2].Data * 8);
	Set(args[0].Data, Data);
}
