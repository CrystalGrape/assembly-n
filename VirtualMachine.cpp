#include "VirtualMachine.h"
#include <iostream>
#include <fstream>
using namespace std;

VirtualMachine::VirtualMachine(int MaxMemorySize)
{
	for (int i = 0; i < 15; i++) {
		R[i] = 0x00000000;
	}
	Memory = new MemoryManager(MaxMemorySize);
	Operators.resize(100);
	Operators[OpCode::MOV] = &VirtualMachine::do_move;
	Operators[OpCode::STR] = &VirtualMachine::do_str;
	Operators[OpCode::LDR] = &VirtualMachine::do_ldr;
	Operators[OpCode::PUSH] = &VirtualMachine::do_push;
	Operators[OpCode::POP] = &VirtualMachine::do_pop;
	Operators[OpCode::JMP] = &VirtualMachine::do_jmp;
	Operators[OpCode::CJMP] = &VirtualMachine::do_cjmp;
	Operators[OpCode::BJMP] = &VirtualMachine::do_bjmp;
	Operators[OpCode::RET] = &VirtualMachine::do_ret;
}

VirtualMachine::~VirtualMachine()
{
	delete Memory;
}

unsigned int VirtualMachine::Get(unsigned int Addr)
{
	if (Addr > RegisterMaxAddr) {
		throw VMExpection(ExpectionCode::OutOfMemory, Addr);
	}

	if (Addr >= RegisterBaseAddr) {
		return R[Addr - RegisterBaseAddr];
	}
	else {
		return Memory->Get(Addr);
	}
}

void VirtualMachine::Set(unsigned int Addr, unsigned int Value)
{
	if (Addr > RegisterMaxAddr) {
		throw VMExpection(ExpectionCode::OutOfMemory, Addr);
	}

	if (Addr >= RegisterBaseAddr) {
		R[Addr - RegisterBaseAddr] = Value;
	}
	else {
		Memory->Set(Addr, Value);
	}
}

void VirtualMachine::LoadModule(std::vector<std::string> &OriginalCode, string moduleName)
{
	string modulePath = moduleName;
	string envPath;
	std::string::size_type startpos = 0;
	int envPathPos = (int)modulePath.find_last_of('.');
	envPath = moduleName.substr(0, moduleName.size() - envPathPos);
	while (startpos != std::string::npos)
	{
		startpos = modulePath.find('.');
		if (startpos != std::string::npos)
		{
			modulePath = modulePath.replace(startpos, 1, "/");
		}
	}

	modulePath += ".asn";

	ifstream srcfile(modulePath);
	if (!srcfile.is_open()){
		throw VMExpection(ModuleNotExist, moduleName);
	}
	char line[8096];
	while (!srcfile.eof()){
		if (!srcfile.getline(line, 8096))
			continue;
		if (Codes.Equals(line, "import", (int)strlen("import")))
		{
			string newModule = line;
			newModule = newModule.substr(7, newModule.size());
			newModule = envPath + newModule;
			LoadModule(OriginalCode, newModule);
			continue;
		}
		OriginalCode.push_back(line);
	}
	srcfile.close();
}

void VirtualMachine::Compile(std::vector<std::string> OriginalCode)
{
	OriginalCode = Codes.PreCompile(OriginalCode);
	for (int i = 0; i < OriginalCode.size(); i++)
	{
		Codes.Add(Codes.ParseData(OriginalCode[i]));
	}
}

void VirtualMachine::ExportExe(string targetName)
{
	Codes.ExportExe(targetName);
}

void VirtualMachine::ImportExe(std::string fromName)
{
	Codes.ImportExe(fromName);
}

void VirtualMachine::Run()
{
	pc = 0;
	sp = 80;
	while (1)
	{
		try
		{
			OperateLine code = Codes.Get(pc++);
			(this->*Operators[code.Cmd])(code.Arg);
		}
		catch (VMExpection e)
		{
			cout << e << endl;
			break;
		}
	}
}

///操作码函数
void VirtualMachine::do_move(OpData args[3])
{
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
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "只能对寄存器进行压栈操作");
	unsigned int opdata = Get(args[0].Data);
	Set(sp++, opdata);
}
void VirtualMachine::do_pop(OpData args[3])
{
	if (args[0].Type != OpDataType::Register)
		throw VMExpection(ArgsError, "只能对寄存器进行退栈操作");
	Set(args[0].Data, Get(--sp));
}
void VirtualMachine::do_jmp(OpData args[3])
{
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
	pc = lr;
}