all: build run

build:
	gcc -std=c17 main.c src/*.c src/commands/*.c -o main.o -lm

run:
	./main.o
