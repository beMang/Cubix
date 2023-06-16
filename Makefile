CC = gcc

main: main.c
	$(CC) $^ -Wall -Wextra $$(sdl2-config --cflags --libs) -o main.out

tests: ./math/operation.c ./math/matrice.c ./tests/matrice_test.c
	$(CC) $^ -Wall -Wextra -o test.out
	./test.out

run: main
	./main.out

.PHONY: tests run