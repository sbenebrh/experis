TARGET=MtThreadLoop
COMMAND=gcc
FLAGS= -g -ansi -pedantic  -Wall -Werror -std=c99 -pthread
all: $(TARGET).c
	@echo Compilimg $(TARGET)
	$(COMMAND)  $(FLAGS) -o $(TARGET) $(TARGET).c
clean:
	rm $(TARGET) 

