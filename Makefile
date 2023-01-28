all: build run

build:
	gcc -std=c17 main.c src/*.c -o main.o -lm

run:
	./main.o
