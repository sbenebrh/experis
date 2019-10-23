
TARGET = insight
TARGET2 = UI
CC 	   = gcc
LFLAGS =  -lLOG -L../AdvanceC/log/lib  -lconfig -lDDS -L../AdvanceC/libD -pthread 
INC_PATH = include
CFLAGS = -pedantic -Wall -I$(INC_PATH) -I../AdvanceC/include -g 
OBJS   =  Insight.o aggrMan.o subAgg.o Subscriber.o QMan.o 
OBJS2 = UI.o  Subscriber.o
AGG_PATH = aggregator
QUERY_PATH = QueryManager
.PHONY: clean all

all:$(TARGET) $(TARGET2)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) $(CPPFLAGS)

$(TARGET2):$(OBJS2) $(INC_PATH)/QMan.h $(INC_PATH)/Subscriber.h
	$(CC) -o $@ $^ $(LFLAGS) $(CPPFLAGS) $(CFLAGS)

Insight.o:Insight.c $(INC_PATH)/QMan.h $(INC_PATH)/aggrMan.h $(INC_PATH)/subAgg.h 
	$(CC) -c $< $(CFLAGS)

aggrMan.o:$(AGG_PATH)/aggrMan.c $(INC_PATH)/subAgg.h
	$(CC) -c $< $(CFLAGS)

subAgg.o:$(AGG_PATH)/subAgg.c $(INC_PATH)/Subscriber.h
	$(CC) -c $< $(CFLAGS)

Subscriber.o:$(AGG_PATH)/Subscriber.c
	$(CC) -c $< $(CFLAGS)

QMan.o:$(QUERY_PATH)/QMan.c $(INC_PATH)/subAgg.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf $(TARGET) $(OBJS) $(TARGET2) $(OBJS2)