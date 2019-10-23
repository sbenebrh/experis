# makefile for signal handling

TARGET = signalhandler
CC = gcc
CFLAGS =  -g -pedantic -Wall 
OBJS = main.o 

.PHONY :  clean run

run: 
	@./$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)


clean:
	rm -rf $(OBJS) $(TARGET)