#pragma once
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum ExpectionCode
{
	EC_Exit = 0,
	EC_ModuleNotExist,
	EC_CodeError,
	EC_OutOfMemory,
	EC_ReadOnly,
	EC_UnexpectionCode,
	EC_ArgsError,
	EC_EntryExternalError,
	EC_CallExternalError,
};

class VMExpection
{
public:
	VMExpection(ExpectionCode ErrCode)
	{
		this->ErrorCode = ErrCode;
	}
	template<class in_value>
	VMExpection(ExpectionCode ErrCode, in_value ErrMsg)
	{
		this->ErrorCode = ErrCode;
		std::stringstream stream;
		stream << ErrMsg;
		stream >> this->ErrorMsg;//��result��д��ֵ
	}

	friend std::ostream &operator<<(std::ostream &os, const VMExpection& e)
	{
		if (e.ErrorCode == EC_Exit)
		{
			os << "���������˳�";
			return os;
		}
		os << "�������:" << e.ErrorCode << std::endl;
		if (e.ErrorMsg.length() != 0)
			os << "������Ϣ:" << e.ErrorMsg.data();
		return os;
	}
private:
	ExpectionCode ErrorCode;
	std::string ErrorMsg;
};