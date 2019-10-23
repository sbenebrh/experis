#include <stdio.h>
#include "notif.h"

int TestPrintDir()
{
	
	char filename[10] = ".";
	MonitorFileSystem(filename);
	return 1;
}


int main()
{
	if(TestPrintDir())
	{
		printf("%s\n","TestPrintDir: PASS"  );
	}
	else
	{
		printf("%s\n","TestPrintDir: FAIL"  );
	}
	return 0;

}