CC			= g++
CFLAGS		= -c -ansi -pedantic -Wall -Wconversion -g -std=c++03 -std=gnu++0x -Iinclude -I../include
LDFLAGS 	=
SOURCES 	= main.cpp Book/Book.cpp  owner/owner.cpp Catalog/Catalog.cpp Author/Author.cpp BookDetails/BookDetails.cpp ISBN/ISBN.cpp Publisher/Publisher.cpp Year/Year.cpp BookReader/BookReader.cpp Parser/Parser.cpp Query/Query.cpp
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
	rm -R *.o $(SOURCES:.cpp=.o) $(EXECUTABLE)  .vscode