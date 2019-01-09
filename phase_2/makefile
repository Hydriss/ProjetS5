CC = gcc
FLAGS = -Wall -Werror

main : ../phase_1/readelf.o main2.o relocation.o
	$(CC) $(FLAGS) -o main ../phase_1/readelf.o main2.o relocation.o

main2.o : main2.c ../phase_1/readelf.h relocation.c
	$(CC) $(FLAGS) -c main2.c

relocation.o : ../phase_1/readelf.h relocation.c
	$(CC) $(FLAGS) -c relocation.c

readelf.o : ../phase_1/readelf.c ../phase_1/readelf.h
	$(CC) $(FLAGS) -c ../phase_1/readelf.c
