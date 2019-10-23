#comment
TARGET=SimpleDebugging
#COMMAND=g++
COMMAND=gcc
#FLAGS= -g -ansi -pedantic  -Wall -Werror -std=c++03
FLAGS= -g3 -ansi -pedantic  -Wall -Werror -std=c99
$(TARGET): $(TARGET).c
	@echo Compilimg $(TARGET)
#	gcc  -g -ansi -pedantic  -Wall -Werror -std=c99 -o SimpleDebugging SimpleDebugging.c
	$(COMMAND)  $(FLAGS) -o $(TARGET) $(TARGET).c
clean:
	rm $(TARGET) 


