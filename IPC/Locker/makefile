#makefile for dynamic library of locker

LIB_NAM 	= LOCKER
CC 			= gcc
CFLAGS 		= -ansi -pedantic -pthread -Wall -g -fPIC
OBJS 		= locker.o
LIB_DIR 	= ../../Dlib
LIB_SO	 	= $(LIB_DIR)/lib$(LIB_NAM).so 
SFLAGS 		= -shared

.phony: clean 

$(LIB_SO): $(OBJS) 
	$(CC)  -o $(LIB_SO)  $(SFLAGS) $(OBJS) 	

locker.o: locker.c
	$(CC) -c $< $(CFLAGS)
clean:
	rm -rf $(LIB_SO) $(OBJS)