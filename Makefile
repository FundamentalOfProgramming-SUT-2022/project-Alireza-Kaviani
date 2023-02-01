all: build run

build:
	gcc -std=c17 main.c src/*.c src/commands/*.c -o main.o -lm

run:
	./main.o

test: build
	rm -rf vimr/tests
	rm -rf vimr/.vim/tests
	for i in tests/*.txt ; do \
		name=$${i%.txt} ; \
        echo "Test $$name" ; \
		./main.o < $$i > $$name.out ; \
		diff $$name.out $$name.ans > /dev/null ; \
		if [ $$? -eq 0 ]; then\
			echo "OK $$name" ; \
		else \
			cat $$name.out ; \
		fi ; \
		echo "=======" ; \
	done ; \
	rm -rf tests/*.out
