CC = gcc

main: ./math/operation.c ./math/matrice.c ./rendering/object.c ./rendering/rendering.c main.c
	$(CC) $^ -Wall -Wextra $$(sdl2-config --cflags --libs) -o bin/main.bin

tests: ./math/operation.c ./math/matrice.c ./rendering/object.c
	$(CC) ./tests/matrice_test.c $^ -Wall -Wextra -o bin/matrice.bin
	$(CC) ./tests/object_test.c $^ -Wall -Wextra -o bin/object.bin

run: main
	./bin/main.bin

clean:
	rm -r bin/*

.PHONY: tests run