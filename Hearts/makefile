#makefile for hearts game

TARGET = hearts
CC = gcc
CFLAGS = -ansi -g -pedantic
OBJS = card.o deck.o players.o round.o trick.o game.o mainWithUser.o vector.o

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

mainWithUser.o : mainWithUser.c 
	$(CC) $(CFLAGS) -c mainWithUser.c

card.o : card.c
	$(CC) $(CFLAGS) -c card.c

deck.o : deck.c
	$(CC) $(CFLAGS) -c deck.c

players.o : players.c
	$(CC) $(CFLAGS) -c players.c

round.o : round.c
	$(CC) $(CFLAGS) -c round.c

trick.o : trick.c
	$(CC) $(CFLAGS) -c trick.c

game.o : game.c
	$(CC) $(CFLAGS) -c game.c

vector.o : vector/vector.c
	$(CC) $(CFLAGS) -c vector/vector.c


clean:
	rm -f $(TARGET)  $(OBJS)