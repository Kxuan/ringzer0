#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>


int main(void) {
    void * func;

    func = mmap(NULL, 4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if ( func == MAP_FAILED) {
        fprintf(stderr, "mmap failed\n");
        return 1;
    }

    int d;
    uint8_t *p = func;
    while(scanf("\\x%02x", &d)) {
        *p++ = (uint8_t)d;
    }
    if (p == func) {
        fprintf(stderr, "no shellcode received\n");
        return 1;
    }
    
    close(0);
    dup2(1, 0);

    ((void (*)())func)();

    return 0;
}
