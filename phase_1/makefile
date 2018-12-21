CC = gcc
FLAGS = -Wall -Werror

readelf : readelf.o main.o
	$(CC) $(FLAGS) -o readelf readelf.o main.o

main.o : main.c readelf.h
	$(CC) $(FLAGS) -c main.c

readelf.o : readelf.c readelf.h
	$(CC) $(FLAGS) -c readelf.c
