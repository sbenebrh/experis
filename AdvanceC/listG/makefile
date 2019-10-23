#makefile for generic list

TARGET = list
CC = gcc
CFLAGS = -g -ansi -pedantic -I../include
OBJS = main.o list.o test.o list_itr.o

$(TARGET) : $(OBJS)
	$(CC)  -o $(TARGET)  $(OBJS)

main.o : test/main.c ../include/list.h
	$(CC) $(CFLAGS) -c test/main.c

list.o: list.c ../include/list.h
	$(CC) $(CFLAGS) -c list.c

test.o: test/test.c ../include/list.h
	$(CC) $(CFLAGS) -c test/test.c

list_itr.o: itr/list_itr.c ../include/list.h
	$(CC) $(CFLAGS) -c itr/list_itr.c

clean:
	rm -f  $(TARGET) $(OBJS)