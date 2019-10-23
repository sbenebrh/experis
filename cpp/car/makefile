CC			= g++
CFLAGS		= -c -Wall -ansi -pedantic -g
LDFLAGS 	=
SOURCES 	= main.cpp car_t.cpp bus.cpp private_t.cpp
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