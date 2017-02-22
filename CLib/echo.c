#include <stdio.h>
#if WINDOWS
	#define ASNExport __declspec(dllexport)
#elif LINUX
	#define ASNExport extern "C"
#endif

typedef struct
{
	void(*push)(unsigned int);
	unsigned int(*pop)();
	void *(*GetPhysicalAddr)(unsigned int);
}RunTime;

ASNExport void echo(RunTime *asnRunTime)
{
	unsigned int Addr = asnRunTime->pop();
	char *data = (char *)asnRunTime->GetPhysicalAddr(Addr);
	printf("%s\n", data);
}