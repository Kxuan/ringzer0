all: sha1
	./solve

sha1: sha1.c
	gcc -g $< -o $@ -lcrypto -std=c99

clean:
	rm -f sha1 tmp
