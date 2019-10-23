#makefile sort


TARGET = sorts
CC = gcc
CFLAGS = -ansi -g -pedantic -I../include -I../../DS/include
OBJS = sorts.o main.o vector.o

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)


sorts.o : sorts.c ../include/sorts.h
	$(CC) $(CFLAGS) -c sorts.c

main.o : main.c ../include/sorts.h
	$(CC) $(CFLAGS) -c main.c

vector.o : ../../DS/vector/vector.c ../../DS/include/vector.h
	$(CC) $(CFLAGS) -c ../../DS/vector/vector.c

clean:
	rm -f $(TARGET)  $(OBJS)