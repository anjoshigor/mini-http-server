# compiler
CC = g++
# flags
FLAGS = -O2 -g3 -pthread -std=c++11 -pedantic -Wall -Werror
# preprocessor directive
PORT = 8080

# >>>>>>>> Rules default to create program <<<<<< #

all: main

main: logger.o main.o socket.o http.o
	$(CC) logger.o main.o socket.o http.o  $(FLAGS) -o main

http.o: http.cpp
	$(CC) http.cpp $(FLAGS) -c

logger.o: logger.cpp
	$(CC) logger.cpp $(FLAGS) -c

main.o: main.cpp
	$(CC) main.cpp -D PORT=$(PORT) $(FLAGS) -c

socket.o: socket.cpp
	$(CC) socket.cpp $(FLAGS) -c

.PHONY: clean

clean:
	rm *.o main

# >>>>>>>>>>>>>>>>>>> END FILE <<<<<<<<<<<<<<<<<<< #