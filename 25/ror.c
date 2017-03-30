#include <stdio.h>

int main(void) {
    int c;
    char base;
    while ((c = getchar()) != EOF) {
        base = 'A';
        if (c > 'a')
            base = 'a';
        
        putchar(base + ((c - base + 13) % 26));
    }
    return 0;
}
