CC := g++
FLAGS := -Wall -O2 -std=c++11 -g

build:
	$(CC) $(FLAGS) -c source/address.cpp -o output/address.o
	$(CC) $(FLAGS) -c source/programm_1.cpp -o output/programm_1.o
	$(CC) $(FLAGS) -c source/programm_2.cpp -o output/programm_2.o

	$(CC) $(FLAGS) output/programm_1.o output/address.o -o output/programm_1
	$(CC) $(FLAGS) output/programm_2.o output/address.o -o output/programm_2