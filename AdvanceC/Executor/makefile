#executor makefile

TARGET= executorTest
CC= gcc
CFLAGS= -g -ansi -pedantic  -I../include -fPIC
OBJS= main.o Executor.o task.o mytime.o vector.o Heap.o zlog4c.o

INC_PATH_DS= ../include/


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c Executor.h  
	$(CC) $(CFLAGS) -c $^
Executor.o: Executor.c mytime.c task.c mytime.h  Task.h $(INC_PATH_DS)Heap.h $(INC_PATH_DS)vector.h Executor.h
	$(CC) $(CFLAGS) -c $^
task.o: task.c Task.h mytime.h
	$(CC) $(CFLAGS) -c $^
mytime.o:  mytime.c mytime.h 
	$(CC) $(CFLAGS) -c $^
vector.o: ../vectorG/vector.c $(INC_PATH_DS)vector.h
	$(CC) $(CFLAGS) -c $^
Heap.o: ../heapG/Heap.c ../vectorG/vector.c $(INC_PATH_DS)Heap.h $(INC_PATH_DS)vector.h
	$(CC) $(CFLAGS) -c $^
zlog4c.o: ../log/zlog4c.c $(INC_PATH_DS)zlog4c.h
	$(CC) $(CFLAGS) -c $^
clean:
	rm -f *.o executorTest 




