install: clean
	mkdir ../bin
	mv es01 ../bin/es01
distclean: clean
	rm -r ../bin

clean: es01
	rm es01.o
es01:
	gcc -c es01.c
	gcc -o es01 es01.o
