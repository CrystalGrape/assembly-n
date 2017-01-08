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
	Operators[OpCode::END] = &VirtualMachine::do_end;
	Operators[OpCode::ADD] = &VirtualMachine::do_add;
	Operators[OpCode::SUB] = &VirtualMachine::do_sub;
	Operators[OpCode::MUL] = &VirtualMachine::do_mul;
	Operators[OpCode::GT] = &VirtualMachine::do_gt;
	Operators[OpCode::GTE] = &VirtualMachine::do_gte;
	Operators[OpCode::LT] = &VirtualMachine::do_lt;
	Operators[OpCode::LTE] = &VirtualMachine::do_lte;
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
#ifdef RECORDTIME
	RecordTime time("load");
#endif
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
#ifdef RECORDTIME
	RecordTime time("compile");
#endif
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
#ifdef RECORDTIME
	RecordTime time("import");
#endif
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