#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

#include <openssl/sha.h>

uint8_t hex_dict[0x100] = {
    [0 ... 0xff] = 0xff,
    ['0'] = 0,
    ['1'] = 1,
    ['2'] = 2,
    ['3'] = 3,
    ['4'] = 4,
    ['5'] = 5,
    ['6'] = 6,
    ['7'] = 7,
    ['8'] = 8,
    ['9'] = 9,
    ['a'] = 10,
    ['b'] = 11,
    ['c'] = 12,
    ['d'] = 13,
    ['e'] = 14,
    ['f'] = 15,
    ['A'] = 10,
    ['B'] = 11,
    ['C'] = 12,
    ['D'] = 13,
    ['E'] = 14,
    ['F'] = 15
};

unsigned hex2bin(const char *hex, char* binary) {
    uint8_t hi, lo;
    char *p = binary;
    while(hex[0] && hex[1] ) {
        do {
            hi = hex_dict[*hex++];
        } while(hi == 0xff && *hex);

        do {
            lo = hex_dict[*hex++];
        } while(lo == 0xff && *hex);

        if (hi != 0xff && lo != 0xff) {
            *p++ = (hi << 4) | lo;
        }
    }
    return p - binary;
}

unsigned bin2hex(const uint8_t *binary, unsigned size, uint8_t * hex) {
    uint8_t *p = hex;
    for (int i = 0; i < size; i++ ) {
       *p = (binary[i] >> 4) + '0';
       if (*p > '9')
            *p = *p - 10 - '0' + 'a';
       
       p++;

       *p = (binary[i] & 0xf) + '0';
       if (*p > '9')
            *p = *p - 10 - '0' + 'a';
       p++;
    }
    *p = 0;
    return p - hex;
}

int search_text(const char* salt, const char* target_hash, char *clear_text) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    size_t salt_len = strlen(salt);
    int n;
    
    for (int i = 1; i < 100000; i++) {
        n = sprintf(clear_text, "%d%s", i, salt);
        SHA1(clear_text, n, hash);
        if (memcmp(hash, target_hash, SHA_DIGEST_LENGTH) == 0) {
            return i;
        }
    }
    
    return 0;
}

void sig_interrupt(int signo) {
    fprintf(stderr, "Timeout\n");
    exit(2);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "%s <salt> <target_hash>\n");
        return 3;
    }
    
    if (strlen(argv[2]) != 2 * SHA_DIGEST_LENGTH) {
        fprintf(stderr, "target_hash: length error\n");
        return 1;
    }

    const char* salt = argv[1];
    static char target_hash[SHA_DIGEST_LENGTH], clear_text[0xff];
    hex2bin(argv[2], target_hash);
    
    signal(SIGALRM, sig_interrupt);
    alarm(2);
    int rc;
    rc = search_text(salt, target_hash, clear_text); 
    if (rc == 0) {
        return 1;
    }

    printf("%d\n", rc);
    return 0;
}
