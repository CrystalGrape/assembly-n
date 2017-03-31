#pragma once

#include <iostream>
#include <vector>
#include <map>
//ָ��
enum OpCode
{
	OC_MOV = 0,
	OC_STR,
	OC_LDR,
	OC_PUSH,
	OC_POP,
	OC_JMP,		//��������ת
	OC_CJMP,		//�ж��Ƿ������ת
	OC_BJMP,		//��������ת
	OC_RET,		//����
	OC_END,		//�����˳�
	OC_ADD,		//��			
	OC_SUB,		//����
	OC_MUL,		//�˷�
	OC_GT,			//����
	OC_GTE,		//���ڵ���
	OC_LT,			//С��
	OC_LTE,		//С�ڵ���
	OC_ENTRY,		//���붯̬��
	OC_CALL,		//���ú���
	OC_EXIT,		//�˳���̬��
	OC_STRB,		//�洢1byte���ݵ��ڴ�
	OC_LDRB,		//����1byte�����ݵ��Ĵ���
	OC_SWI,			//���ж�ָ��
	OC_SWM,			//�л�ģʽ
};

//������������
enum OpDataType
{
	OT_ImmediateData,		//������
	OT_DataPointer,			//ָ��
	OT_Register,			//�Ĵ���
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

