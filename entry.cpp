#include <iostream> 
#include "VirtualMachine.h"
using namespace std;

int main(int argc, char *argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cout << "demo:assembly-n [asn file]" << std::endl;
			return 0;
		}
		std::vector<std::string> OriginalCode;
		VirtualMachine vm(4096);
		vm.LoadModule(OriginalCode, argv[1]);
		vm.Compile(OriginalCode);

		vm.Run();
	}
	catch (VMExpection e)
	{
		cout << e << endl;
	}
	return 0;
}