CC			= g++
CFLAGS		= -c -ansi -pedantic -Wall -Wconversion -g -std=c++03 -std=gnu++0x -Iinclude -I../include -I../advcpp/include -I/LiveLogger -Wno-deprecated -fPIC
LDFLAGS 	= -pthread -lpthread  -lSmokeSensor -lSmokeControler -L./Lib   -export-dynamic -lconfig++ -ldl
SOURCES 	= Test/testflowSensContr.cpp CommonSensor/CommonSensor.cpp   Event/Event.cpp  EventQueue/EventQueue.cpp ../advcpp/Mutex/Mutex.cpp ../advcpp/CondVariable/CondVariable.cpp  Thread/Thread.cpp EventCriterion/EventCriterion.cpp EventDispatcher/EventDispatcher.cpp EventPublisher/EventPublisher.cpp PubImpl/SerialPub.cpp SubRegistry/SubRegistry.cpp  ConfigurationAgent/ConfigurationAgent.cpp AgentsManager/AgentsManager.cpp Location/Location.cpp Parser/Parser.cpp Server/Server.cpp ThreadPool/ThreadPool.cpp LiveLogger/LiveLogger.cpp
OBJECTS		= $(SOURCES:.cpp=.o)
EXECUTABLE	= main


.PHONY: all clean run
all:  $(SOURCES) $(EXECUTABLE) 

run:
	./$(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	

clean:
	rm -R *.o $(SOURCES:.cpp=.o) $(EXECUTABLE)  .vscode