#makefile for string

TARGET = string.out
CC = gcc
CFLAGS = -ansi -g -pedantic -I../include
OBJS = string.o test.o main.o


$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

string.o : string.c ../include/string.h
	$(CC) $(CFLAGS) -c string.c

test.o : test.c test.h ../include/string.h
	$(CC) $(CFLAGS) -c test.c

main.o : main.c test.h ../include/string.h
	$(CC) $(CFLAGS) -c main.c

clean : 
	rm -f $(TARGET) $(OBJS)