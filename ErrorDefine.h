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
		stream >> this->ErrorMsg;//向result中写入值
	}

	friend std::ostream &operator<<(std::ostream &os, const VMExpection& e)
	{
		os << "错误代码:" << e.ErrorCode << std::endl;
		if (e.ErrorMsg.length() != 0)
			os << "错误信息:" << e.ErrorMsg.data() << std::endl;
		return os;
	}
private:
	ExpectionCode ErrorCode;
	std::string ErrorMsg;
};