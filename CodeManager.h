#pragma once

#include <iostream>
#include <vector>
#include <map>
//指令
enum OpCode
{
	OC_MOV = 0,
	OC_STR,
	OC_LDR,
	OC_PUSH,
	OC_POP,
	OC_JMP,		//无条件跳转
	OC_CJMP,		//判断是否溢出跳转
	OC_BJMP,		//带返回跳转
	OC_RET,		//返回
	OC_END,		//程序退出
	OC_ADD,		//加			
	OC_SUB,		//减法
	OC_MUL,		//乘法
	OC_GT,			//大于
	OC_GTE,		//大于等于
	OC_LT,			//小于
	OC_LTE,		//小于等于
	OC_ENTRY,		//进入动态库
	OC_CALL,		//调用函数
	OC_EXIT,		//退出动态库
	OC_STRB,		//存储1byte数据到内存
	OC_LDRB,		//加载1byte的数据到寄存器
	OC_SWI,			//软中断指令
	OC_SWM,			//切换模式
};

//操作数据类型
enum OpDataType
{
	OT_ImmediateData,		//立即数
	OT_DataPointer,			//指针
	OT_Register,			//寄存器
};

#pragma pack(1)
struct OpData
{
	OpDataType Type;
	unsigned int Data;
};
#pragma pack()
#pragma pack(1)
struct OperateLine
{
	OpCode Cmd;
	OpData Arg[3];
};
#pragma pack()

class CodeManager
{
public:
	CodeManager();
	static std::string& Trim(std::string &s);
	static bool Equals(std::string first, std::string next, int len);
	std::vector<std::string> PreCompile(std::vector<std::string> Codes);
	OperateLine ParseData(std::string line);
	//返回当前地址
	unsigned int Add(OperateLine code);
	OperateLine Get(unsigned int Addr);
	void ExportExe(std::string targetName);
	void ImportExe(std::string fromName);
	~CodeManager();
private:
	std::vector<OperateLine> CodeSection;
	std::map<std::string, int> SectionMap;
	std::map<std::string, OpCode> MapCode;
	std::map<std::string, unsigned int> MapRegister;
};

