#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t byte = 0;

void feed_little(char c) {
    byte = (byte << 1) | (c - '0');
}

void feed_big(char c) {
    byte = (byte >> 1) | ((c - '0') << 7);
}

int main(int argc, char* argv[]) {
    int num = 0;
    void (*feed)(char) = feed_little;
    int c;
    

    if (argc == 2 && strcmp(argv[1], "big") == 0) {
        feed = feed_big;
    }

    while((c = getchar()) != EOF) {
        if ( c != '0' && c != '1') 
            continue;
        
        feed((char)c);
        num++;

        if (num % 8 == 0) {
            putchar(byte);
        }
    }
    fprintf(stderr, "%d bits.\n %d remains\n", num, num % 8);

    return 0;
}
