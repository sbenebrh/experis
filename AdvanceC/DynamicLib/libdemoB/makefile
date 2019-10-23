TARGET = libdemoB.so
CC = gcc
CFLAGS = -g -ansi -pedantic -fPIC
OBJS = funcB.o

.PHONY: clean

$(TARGET): $(OBJS)
	$(CC) -o $@ -shared $^

funcB.o:funcB.c

clean:
	rm -f $(TARGET) $(OBJS)