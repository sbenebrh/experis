
CC			= g++
CFLAGS		= -c -Wall -ansi -pedantic -g
LDFLAGS 	=
SOURCES 	= test.cpp string_t.cpp
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