#pragma once

#include <iostream>
#include <vector>
#include <map>
//ָ��
enum OpCode
{
	MOV = 0,
	STR,
	LDR,
	PUSH,
	POP,
	JMP,		//��������ת
	CJMP,		//�ж��Ƿ������ת
	BJMP,		//��������ת
	RET,		//����
	END,		//�����˳�
	ADD,		//��			
	SUB,		//����
	MUL,		//�˷�
	GT,			//����
	GTE,		//���ڵ���
	LT,			//С��
	LTE,		//С�ڵ���
	ENTRY,		//���붯̬��
	CALL,		//���ú���
	EXIT,		//�˳���̬��
};

//������������
enum OpDataType
{
	ImmediateData,		//������
	DataPointer,		//ָ��
	Register,			//�Ĵ���
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
	//���ص�ǰ��ַ
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

