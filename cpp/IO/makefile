CC			= g++
CFLAGS		= -c -ansi -pedantic -g
LDFLAGS 	=
SOURCES 	= main.cpp VirtIO_t.cpp AsciiIO_t.cpp BinIO_t.cpp
OBJECTS		= $(SOURCES:.cpp=.o)
EXECUTABLE	= main

.PHONY: all clean

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	

clean:
	\rm -R *.o $(EXECUTABLE) *.txt .vscode