#pragma once
#include "MemoryManager.h"
#include "CodeManager.h"
#include "CpuExpection.h"
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
	void pushData(Int32 OpData);
	Int32 popData();
	unsigned int *GetPhysicalAddr(unsigned int Addr);
	~VirtualMachine();
private:
	///操作码函数
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
	void do_add(OpData args[3]);
	void do_sub(OpData args[3]);
	void do_mul(OpData args[3]);
	void do_gt(OpData args[3]);
	void do_gte(OpData args[3]);
	void do_lt(OpData args[3]);
	void do_lte(OpData args[3]);
	void do_entry(OpData args[3]);
	void do_call(OpData args[3]);
	void do_exit(OpData args[3]);
	void do_strb(OpData args[3]);
	void do_ldrb(OpData args[3]);
	void do_swi(OpData args[3]);
private:
	//异常处理模块
	bool AllowRun(OpCode code);
	RunModCode CurrentRunMode();
private:
	//0x00000000-0x56000000
	MemoryManager *Memory;
	//0x56000000以上是寄存器
	/*
		R10=PC
		R11=LR
		R12=SP
		R13=DPTR		//指针寄存器
		R14=CPSR		//状态寄存器
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

/*
cpsr 标志位 
0：溢出标志
1，2：运行模式
[
	00:Usr
	01:SVC
	10:SYS
	11:IRQ
]
*/

