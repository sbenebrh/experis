CC			= g++
CFLAGS		=  -fPIC  -ansi -pedantic -Wall -Wconversion -g -std=c++03 -std=gnu++0x  -I../include -I../../advcpp/include -Wno-deprecated 
LFLAGS = -shared
LDFLAGS =   -L../LiveLogger -export-dynamic -ldl
SOURCES = SmokeSensor.cpp FireSensor.cpp SmokeEvent.cpp FireEvent.cpp  SmokeControler.cpp FireControler.cpp ../../advcpp/Mutex/Mutex.cpp 
OBJECTS	= $(SOURCES:.cpp=.o)
EXECUTABLE = libSmokeSensor.so libSmokeControler.so libFireControler.so libFireSensor.so 
INC_PATH = ../include

.PHONY: all clean 
all:  $(SOURCES) $(EXECUTABLE) 

run:
	./$(EXECUTABLE)

libSmokeSensor.so:  SmokeEvent.o SmokeSensor.o  
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

libFireSensor.so: FireSensor.o FireEvent.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LFLAGS)
	
libSmokeControler.so: SmokeControler.o  $(INC_PATH)/IAgent.h
	$(CC) $(LDFLAGS) $^ -o $@ $(LFLAGS)
libFireControler.so: FireControler.o $(INC_PATH)/IAgent.h 
	$(CC) $(LDFLAGS) $^ -o $@ $(LFLAGS)



.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -R *.o $(SOURCES:.cpp=.o) $(EXECUTABLE)  .vscode