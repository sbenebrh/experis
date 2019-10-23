CC			= g++
CFLAGS		= -c -ansi -pedantic -Wall -Wconversion -g -std=c++03 -I../include
LDFLAGS 	=
SOURCES 	= test.cpp 
OBJECTS		= $(SOURCES:.cpp=.o)
EXECUTABLE	= main

.PHONY: all clean run
all: $(SOURCES) $(EXECUTABLE)

run:
	./$(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	

clean:
	rm -R *.o $(EXECUTABLE)  .vscode