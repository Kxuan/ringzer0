#include <stdio.h>


char buffer[0xfffff];

int main(void) {
    size_t n;
    n = fread(buffer, 1, sizeof(buffer), stdin);
    while(n--) {
        putchar(buffer[n]);
    }
    return 0;
}
