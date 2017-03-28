all: _maw _mal _frac
	clang obj/maw.o obj/mal.o obj/frac.o -o maw

_maw:
	clang -Wall -Werror -pedantic -ggdb3 -c -std=c99 examples/maw.c -o obj/maw.o

_mal:
	clang -Wall -Werror -pedantic -ggdb3 -c -std=c99 src/mal.c -o obj/mal.o

_frac:
	clang -Wall -Werror -pedantic -ggdb3 -c -std=c99 src/frac.c -o obj/frac.o

test:
	clang -Wall -Werror -pedantic -std=c99 src/mal.c src/test.c src/frac.c -o test
	./test
	rm test
