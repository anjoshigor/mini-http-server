CC = g++
FLAGS = -std=c++11 -pthread -g3 -O2 -Wall -pedantic

.PHONY: clean

http.o: http.cpp
	$(CC) http.cpp $(FLAGS) -c

LogClass.o: LogClass.cpp
	$(CC) LogClass.cpp $(FLAGS) -c

main.o: main.cpp
	$(CC) main.cpp $(FLAGS) -c

socket.o: socket.cpp
	$(CC) socket.cpp $(FLAGS) -c

main: LogClass.o main.o socket.o http.o
	$(CC) LogClass.o main.o socket.o http.o $(FLAGS) -o main

clean:
	rm *.o main
