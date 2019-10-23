
TARGET = pingpong
CC = gcc
CFLAGS = -ansi -g -pedantic -pthread 
OBJS = wQueue.o producer.o consumers.o main.o

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -pthread

wQueue.o : wQueue.c wQueue.h

producer.o:producer.c wQueue.h

consumers.o: consumers.c wQueue.h

main.o: main.c consumers.h producer.h wQueue.h


clean :
	rm -rf $(TARGET) $(OBJS)