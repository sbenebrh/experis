TARGET = Heap
CC = gcc
CFLAGS = -g -ansi -pedantic -I../include
OBJS = main.o Heap.o test.o vector.o

$(TARGET) : $(OBJS)
	$(CC)  -o $(TARGET)  $(OBJS)

main.o : main.c ../include/queue.h
	$(CC) $(CFLAGS) -c main.c

Heap.o: Heap.c ../include/Heap.h ../include/vector.h
	$(CC) $(CFLAGS) -c Heap.c

test.o: test.c ../include/Heap.h
	$(CC) $(CFLAGS) -c test.c

vector.o: ../vectorG/vector.c ../include/vector.h
	$(CC) $(CFLAGS) -c ../vectorG/vector.c

clean:
	rm -f  $(TARGET) $(OBJS)