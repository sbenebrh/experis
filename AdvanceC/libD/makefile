
TARGET = libDDS.so
TEST = testVector
CC = gcc
CFLAGS = -g  -pedantic -I../include -fPIC -I../../IPC/Locker
CPPFLAGS = -DLD_LIBRARY_PATH=.
LFLAGS = -lLOCKER -L../../IPC/Locker/lib -lLOG -L../log/lib
SFLAGS = -shared
LIB = -lDDS -L.
INC_PATH = ../include
OBJS = vector.o  queue.o hash.o bst.o list.o itr.o itrFunc.o heap.o concurentHash.o
OBJ1 = test.o main.o

.PHONY: clean all

all:$(TARGET) $(TEST)

$(TARGET): $(OBJS) 
	$(CC)  -o $(TARGET)  $(SFLAGS) $(OBJS) 	$(LFLAGS)

$(TEST):$(OBJ1) $(TARGET)
	$(CC) -o $@ $(LIB) $^ $(CPPFLAGS)

test.o: ../vectorG/test.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LFLAGS)

main.o: ../vectorG/main.c
	$(CC) $(CFLAGS) -o $@ -c $<
vector.o : ../vectorG/vector.c $(INC_PATH)/vector.h
	$(CC) $(CFLAGS) -o $@  -c $<

queue.o:../queueG/queue.c	$(INC_PATH)/queue.h
	$(CC) $(CFLAGS) -o $@  -c $<

hash.o:../HashMap/HashMap.c	$(INC_PATH)/HashMap.h
	$(CC) $(CFLAGS) -o $@  -c $<

bst.o:../BSTG/bin_tree.c	$(INC_PATH)/bin_tree.h
	$(CC) $(CFLAGS) -o $@  -c $<

list.o:../listG/list.c	$(INC_PATH)/list.h
	$(CC) $(CFLAGS) -o $@  -c $<

itr.o:../listG/itr/list_itr.c ../listG/itr/list_functions.c	$(INC_PATH)/list.h
	$(CC) $(CFLAGS) -o $@  -c $<

itrFunc.o: ../listG/itr/list_functions.c ../listG/itr/list_itr.c 	$(INC_PATH)/list.h
	$(CC) $(CFLAGS) -o $@  -c $<

heap.o:../heapG/Heap.c	../vectorG/vector.c $(INC_PATH)/Heap.h
	$(CC) $(CFLAGS) -o $@  -c $<
	
concurentHash.o:../ConcurentHash2/ConcurentHash.c $(INC_PATH)/HashMap.h  
	$(CC) $(CFLAGS) -o $@  -c $< $(LFLAGS)

clean:
	rm -f  $(TARGET)  $(OBJS) $(OBJ1) $(TEST)
