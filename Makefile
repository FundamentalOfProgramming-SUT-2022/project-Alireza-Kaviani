all: build run

build:
	gcc -std=c17 main.c src/*.c src/commands/*.c -o main.o -lm

run:
	./main.o

test: build
	rm -rf vimr/tests
	rm -rf vimr/.vim/tests
	for i in tests/*.txt ; do \
        echo $$i ; \
		./main.o < $$i ; \
		echo "=======" ; \
	done
