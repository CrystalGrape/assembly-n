#pragma once
#include <iostream>
#include <sstream>
typedef enum 
{
	Exit = 0,
	ModuleNotExist,
	CodeError,
	OutOfMemory,
	ReadOnly,
	UnexpectionCode,
	ArgsError,
	EntryExternalError,
	CallExternalError,
}ExpectionCode;
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
		if (e.ErrorCode == ExpectionCode::Exit)
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