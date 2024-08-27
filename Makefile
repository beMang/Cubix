CC = g++

main: ./math/operation.cpp ./math/matrice.cpp ./rendering/camera.cpp ./events/event.cpp ./rendering/face.cpp ./rendering/object.cpp ./loader/obj_file_loader.cpp ./rendering/rendering.cpp main.cpp -lm
	$(CC) $^ -Wall -Wextra $$(sdl2-config --cflags --libs) -g -o bin/main.bin

run: main
	./bin/main.bin

clean:
	rm -r bin/*

little:
	$(CC) test.c -Wall -Wextra $$(sdl2-config --cflags --libs) -g -o bin/little.bin

.PHONY: tests run