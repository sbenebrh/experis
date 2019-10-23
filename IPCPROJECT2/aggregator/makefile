
TARGET 	= aggMan.o
CC 		= gcc
CFLAGS 	= -g  -pedantic -Iinclude -fPIC -I../IPC/Locker -I../AdvanceC/include -DLD_LIBRARY_PATH=.
LFLAGS 	= -lLOG -L../AdvanceC/log/lib -lDDS -L../AdvanceC/libD

aggMan.o:aggrMan.c  
	$(CC) $(CFLAGS) -o $@  -c $< $(LFLAGS)