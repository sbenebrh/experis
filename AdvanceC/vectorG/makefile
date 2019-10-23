#makefile for generic vector

TARGET = vector
CC = gcc
CFLAGS = -g -ansi -pedantic -I../include
OBJS = main.o vector.o test.o

$(TARGET) : $(OBJS)
	$(CC)  -o $(TARGET)  $(OBJS)

main.o : main.c ../include/vector.h
	$(CC) $(CFLAGS) -c main.c

vector.o: vector.c ../include/vector.h
	$(CC) $(CFLAGS) -c vector.c

test.o: test.c ../include/vector.h
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f  $(TARGET) $(OBJS)