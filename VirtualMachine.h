#pragma once
#include "MemoryManager.h"
#include "CodeManager.h"
typedef unsigned int Int32;
#define RegisterBaseAddr 0x56000000
#define RegisterMaxAddr 0x56000014
class VirtualMachine
{
public:
	VirtualMachine(int MaxMemorySize);
	unsigned int Get(unsigned int Addr);
	void Set(unsigned int Addr, unsigned int Value);
	void LoadModule(std::vector<std::string> &OriginalCode, std::string moduleName);
	void Compile(std::vector<std::string> OriginalCode);
	void ExportExe(std::string targetName);
	void ImportExe(std::string fromName);
	void Run();
	~VirtualMachine();
private:
	///²Ù×÷Âëº¯Êý
	void do_move(OpData args[3]);
	void do_str(OpData args[3]);
	void do_ldr(OpData args[3]);
	void do_push(OpData args[3]);
	void do_pop(OpData args[3]);
	void do_jmp(OpData args[3]);
	void do_cjmp(OpData args[3]);
	void do_bjmp(OpData args[3]);
	void do_ret(OpData args[3]);
	void do_end(OpData args[3]);
private:
	//0x00000000-0x56000000
	MemoryManager *Memory;
	//0x56000000ÒÔÉÏÊÇ¼Ä´æÆ÷
	/*
		R10=PC
		R11=LR
		R12=SP
		R13=DPTR		//Ö¸Õë¼Ä´æÆ÷
		R14=CPSR		//×´Ì¬¼Ä´æÆ÷
	*/
	Int32 R[15];
	CodeManager Codes;
#define pc R[10]
#define lr R[11]
#define sp R[12]
#define dptr R[13]
#define cpsr R[14]
	typedef void (VirtualMachine::*OperatorFunction)(OpData args[3]);
	std::vector<OperatorFunction> Operators;
};


