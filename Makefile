CC = g++
CFLAGS = -g -Wall -Wextra

TARGET = deque

default: all

all: main.o deque.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o deque.o

deque.o: deque.cpp deque.h
	$(CC) $(CFLAGS) -c deque.cpp

main.o: main.cpp deque.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) $(TARGET) *.o *~
