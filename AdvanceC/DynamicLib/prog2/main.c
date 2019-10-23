#include<stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include<string.h>
#define MAXPATH 512

static void load(char* loadfunc, char* path)
{
	void (*func)(void);
	void* handle;
	char *error;

	handle = dlopen(path, RTLD_LAZY);
	if (!handle) 
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	*(void **) (&func) = dlsym(handle, loadfunc);
	if ((error = dlerror()) != NULL)  
	{
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
	(*func)();
	dlclose(handle);
}
static void loadLib(char _choice)
{

	char *loadfunc = malloc (6 * sizeof(char));
	char *path = malloc (MAXPATH * sizeof(char));
	switch(_choice)
	{
		case 'A':
			strcpy(path , "../libdemoA/libdemoA.so");
    		strcpy(loadfunc , "funcA");
			break;
		case 'B':
			strcpy(path , "../libdemoB/libdemoB.so");
    		strcpy(loadfunc ,"funcB");
			break;
		default:
			return;

	}
	load(loadfunc, path);
}

int main()
{
	char c;
	printf("%s\n","hi what do you want to do(A/B)" );
	scanf("%c", &c);

	loadLib(c);
}