CC = g++

main: ./math/*.cpp ./objects/object.cpp ./objects/mesh.cpp ./objects/face.cpp ./main.cpp
	$(CC) $^ -Wall -Wextra $$(sdl2-config --cflags --libs) -g -o bin/main.bin

run: main
	./bin/main.bin

clean:
	rm -r bin/*

little:
	$(CC) test.c -Wall -Wextra $$(sdl2-config --cflags --libs) -g -o bin/little.bin

.PHONY: tests run