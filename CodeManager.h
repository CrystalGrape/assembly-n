#pragma once

#include <iostream>
#include <vector>
#include <map>
//指令
enum OpCode
{
	MOV = 0,
	STR,
	LDR,
	PUSH,
	POP,
	JMP,		//无条件跳转
	CJMP,		//判断是否溢出跳转
	BJMP,		//带返回跳转
	RET,		//返回
	END,		//程序退出
	ADD,		//加			
	SUB,		//减法
	MUL,		//乘法
	GT,			//大于
	GTE,		//大于等于
	LT,			//小于
	LTE,		//小于等于
	ENTRY,		//进入动态库
	CALL,		//调用函数
	EXIT,		//退出动态库
};

//操作数据类型
enum OpDataType
{
	ImmediateData,		//立即数
	DataPointer,		//指针
	Register,			//寄存器
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
	std::string& CodeManager::Trim(std::string &s);
	bool Equals(std::string first, std::string next, int len);
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

