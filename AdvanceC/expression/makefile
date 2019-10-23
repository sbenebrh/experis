#makefile for expression tree



TARGET = expressionTreeTest
CC = gcc
CFLAGS = -ansi -g -pedantic -Wall  -I../include 
INC = ../include
OBJS   =  test.o  HashMap.o list.o list_itr.o list_functions.o expTree.o ExpressionParser.o

.PHONY: clean

$(TARGET):$(OBJS)
	$(CC)  -o $(TARGET) $(OBJS) -lm

ExpressionParser.o:ExpressionParser.c $(INC)/HashMap.h
	$(CC) $(CFLAGS) -c $<
test.o:test.c expTree.h
	$(CC) $(CFLAGS) -c $<

HashMap.o: ../HashMap/HashMap.c $(INC)/list_functions.h $(INC)/list_itr.h $(INC)/list.h
	$(CC) $(CFLAGS) -c $<

list.o: ../listG/list.c
	$(CC) $(CFLAGS) -c $<

list_itr.o: ../listG/itr/list_itr.c $(INC)/list.h
	$(CC) $(CFLAGS) -c $<

list_functions.o: ../listG/itr/list_functions.c $(INC)/list_itr.h $(INC)/list.h
	$(CC) $(CFLAGS) -c $<

expTree.o: expTree.c $(INC)/HashMap.h
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -rf $(TARGET) $(OBJS)
