#include "VirtualMachine.h"
#include <iostream>
#include <fstream>
#include "ExternalCall.h"
using namespace std;

VirtualMachine::VirtualMachine(int MaxMemorySize)
{
	for (int i = 0; i < 15; i++) {
		R[i] = 0x00000000;
	}
	Memory = new MemoryManager(MaxMemorySize);
	Operators.resize(100);
	Operators[OC_MOV] = &VirtualMachine::do_move;
	Operators[OC_STR] = &VirtualMachine::do_str;
	Operators[OC_LDR] = &VirtualMachine::do_ldr;
	Operators[OC_PUSH] = &VirtualMachine::do_push;
	Operators[OC_POP] = &VirtualMachine::do_pop;
	Operators[OC_JMP] = &VirtualMachine::do_jmp;
	Operators[OC_CJMP] = &VirtualMachine::do_cjmp;
	Operators[OC_BJMP] = &VirtualMachine::do_bjmp;
	Operators[OC_RET] = &VirtualMachine::do_ret;
	Operators[OC_END] = &VirtualMachine::do_end;
	Operators[OC_ADD] = &VirtualMachine::do_add;
	Operators[OC_SUB] = &VirtualMachine::do_sub;
	Operators[OC_MUL] = &VirtualMachine::do_mul;
	Operators[OC_GT] = &VirtualMachine::do_gt;
	Operators[OC_GTE] = &VirtualMachine::do_gte;
	Operators[OC_LT] = &VirtualMachine::do_lt;
	Operators[OC_LTE] = &VirtualMachine::do_lte;
	Operators[OC_ENTRY] = &VirtualMachine::do_entry;
	Operators[OC_CALL] = &VirtualMachine::do_call;
	Operators[OC_EXIT] = &VirtualMachine::do_exit;
	Operators[OC_STRB] = &VirtualMachine::do_strb;
	Operators[OC_LDRB] = &VirtualMachine::do_ldrb;
	Operators[OC_ALLOC] = &VirtualMachine::do_alloc;
	ExternalCall::GetInstance()->SetRunTime(this);
	StackMemory = new Alloc(100, 512);
}

VirtualMachine::~VirtualMachine()
{
	delete Memory;
	delete StackMemory;
}

unsigned int VirtualMachine::Get(unsigned int Addr)
{
	if (Addr > RegisterMaxAddr) {
		throw VMExpection(EC_OutOfMemory, Addr);
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
		throw VMExpection(EC_OutOfMemory, Addr);
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
	if (envPathPos == -1)
		envPath = "";
	else
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

	ifstream srcfile(modulePath.data());
	if (!srcfile.is_open()){
		throw VMExpection(EC_ModuleNotExist, moduleName);
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
	for (int i = 0; i < (int)OriginalCode.size(); i++)
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

void VirtualMachine::pushData(Int32 OpData)
{
	Set(sp++, OpData);
}
Int32 VirtualMachine::popData()
{
	return Get(--sp);
}
unsigned int *VirtualMachine::GetPhysicalAddr(unsigned int Addr)
{
	return Memory->GetPhysicalAddr(Addr);
}