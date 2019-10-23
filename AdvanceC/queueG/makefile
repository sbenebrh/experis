TARGET = queue
CC = gcc
CFLAGS = -g -ansi -pedantic -I../include
OBJS = main.o queue.o test.o

$(TARGET) : $(OBJS)
	$(CC)  -o $(TARGET)  $(OBJS)

main.o : main.c ../include/queue.h
	$(CC) $(CFLAGS) -c main.c

queue.o: queue.c ../include/queue.h
	$(CC) $(CFLAGS) -c queue.c

test.o: test.c ../include/queue.h
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f  $(TARGET) $(OBJS)