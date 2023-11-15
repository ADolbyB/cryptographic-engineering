#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(char in[]) {
    size_t len = strlen(in);
    char *out;
    out = malloc(len + 2);
    memcpy(out, in, len);
    out[len] = '\n';
    printf(out);
}

void print_hex_bytes(const unsigned char *in, size_t len) {
    printf("0x");
    for(int i = 0; i < len; i++) {
        printf("%02X", (unsigned char)in[i]);
    }
    printf("\n");
}