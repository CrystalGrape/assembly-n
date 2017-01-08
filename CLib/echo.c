#include <stdio.h>

typedef struct
{
	void(*push)(unsigned int);
	unsigned int(*pop)();
	void *(*GetPhysicalAddr)(unsigned int);
}RunTime;

__declspec(dllexport) void echo(RunTime *asnRunTime)
{
	unsigned int Addr = asnRunTime->pop();
	char *data = (char *)asnRunTime->GetPhysicalAddr(Addr);
	printf("%s\n", data);
}