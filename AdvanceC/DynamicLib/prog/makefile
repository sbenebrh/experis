#makefile for functions using dynamic lib

TARGET1 = prog
TARGET2 = libx.so
CC = gcc
CFLAGS = -g -ansi -pedantic -I../libx
LFLAGS = -fPIC
SFLAGS = -shared
LIB = -lx -L.
OBJS = a.o b.o c.o
OBJSLIB = x1.o x2.o x3.o

all :  libx.so prog

libx.so : $(OBJSLIB)
	$(CC)  -o $(TARGET2) $(SFLAGS)	$(OBJSLIB)
	
prog : $(OBJS) 
	$(CC)  -o $(TARGET1)  $(OBJS) $(LIB)



a.o : a.c prog.h 
	$(CC) $(CFLAGS) -c a.c

b.o : b.c prog.h  
	$(CC) $(CFLAGS) -c b.c

c.o : c.c prog.h
	$(CC) $(CFLAGS) -c c.c

x1.o : ../libx/x1.c ../libx/libx.h
	$(CC) $(LFLAGS) -c ../libx/x1.c

x2.o : ../libx/x2.c ../libx/libx.h
	$(CC) $(LFLAGS) -c ../libx/x2.c

x3.o : ../libx/x3.c ../libx/libx.h
	$(CC) $(LFLAGS) -c ../libx/x3.c

clean:
	rm -f  $(TARGET1) $(OBJS) $(TARGET2) $(OBJSLIB)