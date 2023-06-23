CC = gcc

main: ./math/operation.c ./math/matrice.c ./rendering/camera.c ./rendering/object.c ./rendering/rendering.c main.c -lm
	$(CC) $^ -Wall -Wextra $$(sdl2-config --cflags --libs) -g -o bin/main.bin

tests: ./math/operation.c ./math/matrice.c ./rendering/object.c
	$(CC) ./tests/matrice_test.c $^ -Wall -Wextra -o bin/matrice.bin -lm
	$(CC) ./tests/object_test.c $^ -Wall -Wextra -o bin/object.bin -lm

run: main
	./bin/main.bin

clean:
	rm -r bin/*

little:
	$(CC) test.c -Wall -Wextra $$(sdl2-config --cflags --libs) -g -o bin/little.bin

.PHONY: tests run