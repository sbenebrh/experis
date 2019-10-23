CC			= g++
CFLAGS		= -c -Wall -ansi -pedantic -g
LDFLAGS 	=
SOURCES 	= main.cpp memManager_t.cpp memPage_t.cpp memPool_t.cpp
OBJECTS		= $(SOURCES:.cpp=.o)
EXECUTABLE	= main

.PHONY: all clean

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	

clean:
	\rm *.o $(EXECUTABLE)