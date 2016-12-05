#pragma once
#include <iostream>
#include <sstream>
enum ExpectionCode
{
	OutOfMemory,
	ReadOnly,
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
		os << "�������:" << e.ErrorCode << std::endl;
		if (e.ErrorMsg.length() != 0)
			os << "������Ϣ:" << e.ErrorMsg.data() << std::endl;
		return os;
	}
private:
	ExpectionCode ErrorCode;
	std::string ErrorMsg;
};