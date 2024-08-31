CC = g++

main: ./math/*.cpp ./objects/*.cpp ./app/*.cpp ./rendering/*.cpp ./main.cpp
	$(CC) -std=c++17 -Wall -Wextra $^ $$(sdl2-config --cflags --libs) -g -o bin/main.bin

run: main
	./bin/main.bin

clean:
	rm -r bin/*

little:
	$(CC) test.c -Wall -Wextra $$(sdl2-config --cflags --libs) -g -o bin/little.bin

.PHONY: tests run