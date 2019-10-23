TARGET = CHash
CC = gcc
CFLAGS =  -g -pedantic -Wall  -I../include -pthread -I../../IPC/Locker
INC = ../include
OBJS   =  test.o  HashMap.o list.o list_itr.o list_functions.o ConcurentHash.o zlog4c.o locker.o 

.PHONY: clean

$(TARGET):$(OBJS)
	$(CC)  -o $(TARGET) $(OBJS) 

zlog4c.o:../log/zlog4c.c
	$(CC) $(CFLAGS) -c $<

locker.o: ../../IPC/Locker/locker.c 
	$(CC) $(CFLAGS) -c $<
	
test.o:test.c $(INC)/ConcurentHash.h
	$(CC) $(CFLAGS) -c $<

HashMap.o: ../HashMap/HashMap.c $(INC)/list_functions.h $(INC)/list_itr.h $(INC)/list.h
	$(CC) $(CFLAGS) -c $<

list.o: ../listG/list.c
	$(CC) $(CFLAGS) -c $<

list_itr.o: ../listG/itr/list_itr.c $(INC)/list.h
	$(CC) $(CFLAGS) -c $<

list_functions.o: ../listG/itr/list_functions.c $(INC)/list_itr.h $(INC)/list.h
	$(CC) $(CFLAGS) -c $<

ConcurentHash.o: ConcurentHash.c $(INC)/zlog4c.h ../../IPC/Locker/locker.h $(INC)/HashMap.h

clean: 
	rm -rf $(TARGET) $(OBJS)