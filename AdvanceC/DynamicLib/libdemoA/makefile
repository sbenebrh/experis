TARGET = libdemoA.so
CC = gcc
CFLAGS = -g -ansi -pedantic -fPIC
OBJS = funcA.o

.PHONY: clean

$(TARGET): $(OBJS)
	$(CC) -o $@ -shared $^

funcA.o:funcA.c

clean:
	rm -f $(TARGET) $(OBJS)