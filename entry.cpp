#include <iostream> 
#include "VirtualMachine.h"
using namespace std;

int main()
{
	try
	{
		std::vector<std::string> OriginalCode;
		VirtualMachine vm(4096);
		/*vm.ImportExe("demo.n");*/
		vm.LoadModule(OriginalCode, "demo.main");
		vm.Compile(OriginalCode);
		
		vm.Run();
	}
	catch (VMExpection e)
	{
		cout << e << endl;
	}
	return 0;
}