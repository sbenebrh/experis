#makefile for file Process

TARGET = files
TARGET2 = fHandler
CC 	   = gcc
CFLAGS = -pedantic -Wall -I../../AdvanceC/include -g -I$(INC_PATH)
OBJS1   =  fMonitor.o 
OBJS2 	= fileHandler.o
LFLAGS =  -lLOG -L../../AdvanceC/log/lib  -lconfig
INC_PATH = ../include

.PHONY: clean all

all:$(TARGET) $(TARGET2)
	
$(TARGET):$(OBJS1)
	$(CC) -o $@ $^ $(LFLAGS)

$(TARGET2):$(OBJS2)
	$(CC) -o $@ $^ $(LFLAGS)

fileHandler.o:fileHandler.c $(INC_PATH)/cdr.h
	gcc -c $< $(CFLAGS)
fMonitor.o:fMonitor.c 
	gcc -c $< $(CFLAGS)

	

clean:
	rm -rf $(TARGET) $(OBJS1) $(OBJS2) $(TARGET2)

