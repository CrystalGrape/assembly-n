#include "CodeManager.h"
#include "ErrorDefine.h"
#include <fstream>
using namespace std;

CodeManager::CodeManager()
{
	MapCode["mov"] = OC_MOV;
	MapCode["ldr"] = OC_LDR;
	MapCode["str"] = OC_STR;
	MapCode["push"] = OC_PUSH;
	MapCode["pop"] = OC_POP;
	MapCode["jmp"] = OC_JMP;
	MapCode["cjmp"] = OC_CJMP;
	MapCode["bjmp"] = OC_BJMP;
	MapCode["ret"] = OC_RET;
	MapCode["end"] = OC_END;
	MapCode["add"] = OC_ADD;
	MapCode["sub"] = OC_SUB;
	MapCode["mul"] = OC_MUL;
	MapCode["gt"] = OC_GT;
	MapCode["gte"] = OC_GTE;
	MapCode["lt"] = OC_LT;
	MapCode["lte"] = OC_LTE;
	MapCode["entry"] = OC_ENTRY;
	MapCode["call"] = OC_CALL;
	MapCode["exit"] = OC_EXIT;
	MapCode["strb"] = OC_STRB;
	MapCode["ldrb"] = OC_LDRB;
	MapCode["swi"] = OC_SWI;
	/*MapCode["alloc"] = OC_ALLOC;
	MapCode["free"] = OC_FREE;*/

	MapRegister["r0"]	=	0x56000000;
	MapRegister["r1"]	=	0x56000001;
	MapRegister["r2"]	=	0x56000002;
	MapRegister["r3"]	=	0x56000003;
	MapRegister["r4"]	=	0x56000004;
	MapRegister["r5"]	=	0x56000005;
	MapRegister["r6"]	=	0x56000006;
	MapRegister["r7"]	=	0x56000007;
	MapRegister["r8"]	=	0x56000008;
	MapRegister["r9"]	=	0x56000009;
	MapRegister["r10"]	=	0x5600000A;
	MapRegister["r11"]	=	0x5600000B;
	MapRegister["r12"]	=	0x5600000C;
	MapRegister["r13"]	=	0x5600000D;
	MapRegister["r14"]	=	0x5600000E;
	MapRegister["pc"]	=	0x5600000A;
	MapRegister["lr"]	=	0x5600000B;
	MapRegister["sp"]	=	0x5600000C;
	MapRegister["dptr"]	=	0x5600000D;
	MapRegister["cpsr"]	=	0x5600000E;
}
CodeManager::~CodeManager()
{
	CodeSection.clear();
	SectionMap.clear();
	MapCode.clear();
	MapRegister.clear();
}
/*取出空格和制表符*/
string& CodeManager::Trim(string &s)
{
	if (s.empty())
	{
		return s;
	}
	size_t index;
	if ((index = s.find_first_not_of("\t")) != string::npos)
		s.erase(0, index);
	if ((index = s.find_first_not_of(" ")) != string::npos)
		s.erase(0, index);
	if ((index = s.find_last_not_of("\t")) != string::npos)
		s.erase(index + 1);
	if ((index = s.find_last_not_of(" ")) != string::npos)
		s.erase(index + 1);
	return s;
}

bool CodeManager::Equals(std::string first, std::string next, int len)
{
	if (len >= (int)first.size())
		len = (int)first.size();
	if (len >= (int)next.size())
		len = (int)next.size();
	for (int i = 0; i < len; i++)
	{
		if (first.data()[i] != next.data()[i])
			return false;
	}
	return true;
}

std::vector<std::string> CodeManager::PreCompile(std::vector<std::string> Codes)
{
	vector<std::string> destCodes;
	int pc = 0;
	for (int i = 0; i < (int)Codes.size(); i++)
	{
		Trim(Codes[i]);

		if (Equals(Codes[i], "section", (int)strlen("section")))
		{
			string SectionName = Codes[i].substr(8, Codes[i].size());
			SectionName = SectionName.substr(0, SectionName.size() - 1);
			SectionMap[SectionName] = pc;
			continue;
		}

		if (Equals(Codes[i], ";", (int)strlen(";")))
		{
			continue;
		}
		destCodes.push_back(Codes[i]);
		pc = (int)destCodes.size();
	}
	return destCodes;
}

OperateLine CodeManager::ParseData(std::string line)
{
	std::string OpCode;
	std::string Arg[3];
	int index = 0;
	for (int i = 0; i < (int)line.size(); i++)
	{
		if (index == 0 && line.data()[i] == ' ')
		{
			index++;
			continue;
		}
		if (line.data()[i] == ',')
		{
			index++;
			continue;
		}

		switch (index)
		{
		case 0:
			OpCode.push_back(line.data()[i]);
			break;
		case 1:
			Arg[0].push_back(line.data()[i]);
			break;
		case 2:
			Arg[1].push_back(line.data()[i]);
			break;
		case 3:
			Arg[2].push_back(line.data()[i]);
			break;
		default:
			throw VMExpection(EC_CodeError, line + "错误");
		}
	}
	OperateLine CodeLine;
	CodeLine.Cmd = MapCode[OpCode];
	for (int i = 0; i < index; i++){
		if (SectionMap.find(Arg[i]) != SectionMap.end())
		{
			CodeLine.Arg[i].Type = OT_ImmediateData;
			CodeLine.Arg[i].Data = SectionMap[Arg[i]];
		}
		else if (MapRegister.find(Arg[i]) != MapRegister.end())
		{
			CodeLine.Arg[i].Type = OT_Register;
			CodeLine.Arg[i].Data = MapRegister[Arg[i]];
		}
		else if (Arg[i].data()[0] == '#')
		{
			CodeLine.Arg[i].Type = OT_DataPointer;
			Arg[i] = Arg[i].substr(1, Arg[i].size());
			CodeLine.Arg[i].Data = atoi(Arg[i].data());
		}
		else
		{
			CodeLine.Arg[i].Type = OT_ImmediateData;
			CodeLine.Arg[i].Data = atoi(Arg[i].data());
		}
	}
	return CodeLine;
}

unsigned int CodeManager::Add(OperateLine code)
{
	CodeSection.push_back(code);
	return (unsigned int)(CodeSection.size() - 1);
}

OperateLine CodeManager::Get(unsigned int Addr)
{
	if (Addr >= CodeSection.size())
		throw VMExpection(EC_UnexpectionCode, "未知代码地址");
	return CodeSection[Addr];
}

void CodeManager::ExportExe(string targetName)
{
	ofstream targetStream(targetName.data(), std::ios::binary);

	for (int i = 0; i < (int)CodeSection.size(); i++)
	{
		targetStream.write((char *)&CodeSection[i], sizeof(OperateLine));
	}
}
void CodeManager::ImportExe(std::string fromName)
{
	ifstream targetStream(fromName.data(), std::ios::binary);

	while (!targetStream.eof())
	{
		OperateLine Code;
		targetStream.read((char *)&Code, sizeof(OperateLine));
		CodeSection.push_back(Code);
	}
}