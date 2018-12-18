CC = gcc
FLAGS = -Wall -Werror

readelf : readelf.o
	$(CC) $(FLAGS) -o readelf readelf.o

readelf.o : readelf.c
	$(CC) $(FLAGS) -c readelf.c
