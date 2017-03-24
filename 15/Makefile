all: reverse nosleep.so
	./solve

reverse: reverse.o
	gcc -o $@ $<

nosleep.so: nosleep.c
	gcc -fPIC -c nosleep.c
	gcc -shared -o nosleep.so nosleep.o
	
clean:
	rm -f *.o tmp* reverse nosleep.so
