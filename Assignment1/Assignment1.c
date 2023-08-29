#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BENCH_LOOPS 1000

// a mod p1
uint64_t modp1(uint64_t a) {
    const uint64_t p1 = 0x0001FFFF;
    uint64_t r;

    // Write 1a here

    return r;
}

// a mod p2
uint64_t modp2(uint64_t a) {
    const uint64_t p2 = 0x03FFFFFB;
    uint64_t r;

    // Write 1b here

    return r;
}

// a mod b
uint64_t modb(uint64_t a) {
    const uint64_t b = 0x00010000;
    uint64_t r;

    // Write 1c here

    return r;
}

// a^-1 mod p1 using FLT
uint64_t FLT(uint64_t a){
    const uint64_t p1 = 0x0001FFFF;
    int i;
    uint64_t r = a;

    // Write 2a here

    return r;
}

// a^-1 mod p1 using EEA
uint64_t EEA(uint64_t in){
    const uint64_t p1 = 0x0001FFFF;
    int64_t a = p1;
    int64_t b = in;

    int64_t u = 1;
    int64_t v = 0;
    int64_t d = a;
    int64_t v1 = 0;
    int64_t v3 = b;
    int64_t q, t1, t3;

    // Write 2b here

    return v;
}

int main(){
    //ex.1
    const uint64_t a1 = 0x3fffffee;
    printf("###############################\n");
    printf("Exercise 1:\n");
    printf("###############################\n");
    printf("a modulo p1 = %lx\n", modp1(a1));
    printf("a modulo p2 = %lx\n", modp2(a1));
    printf("a modulo b = %lx\n", modb(a1));
    printf("###############################\n\n");

    //ex.2
    const uint64_t a2 = 51;
    printf("###############################\n");
    printf("Exercise 2:\n");
    printf("###############################\n");
    printf("Multiplication inverse of 51 using FLT = %lx\n", FLT(a2));
    printf("Multiplication inverse of 51 using EEA = %lx\n", EEA(a2));
    printf("###############################\n\n");

    //ex.3
    int i;
    unsigned long long cycles, cycles1, cycles2;
    FILE *urandom = fopen("/dev/urandom","r");  //for random input
    uint64_t a3;

    fclose(urandom);
    printf("###############################\n\n");

    // Test bank:
    printf("###############################\n");
    printf("Test Bank:\n");
    printf("###############################\n");
    int j;
    uint64_t a_bank;
    uint64_t exp_bank;
    uint64_t res_bank;
    const int BANK_TOTAL = 1000;

    FILE *fbank = fopen("assign1_bank","r"); 

    if (fbank == NULL) {
        printf("'assign1_bank' file is missing. Please copy it to the same directory as where you execute the code.\n");
        return 1;
    }

    for (j = 0; j < BANK_TOTAL; j++) {
        fread(&a_bank, sizeof(uint64_t), 1, fbank);
        fread(&exp_bank, sizeof(uint64_t), 1, fbank);

        res_bank = modp1(a_bank);
        if(res_bank != exp_bank) {
            printf("modp1 failed for these values:\n");
            printf("a   = %lx\n", a_bank);
            printf("exp = %lx\n", exp_bank);
            printf("res = %lx\n", res_bank);
            return 2;
        }
    }

    for (j = 0; j < BANK_TOTAL; j++) {
        fread(&a_bank, sizeof(uint64_t), 1, fbank);
        fread(&exp_bank, sizeof(uint64_t), 1, fbank);

        res_bank = modp2(a_bank);
        if(res_bank != exp_bank) {
            printf("modp2 failed for these values:\n");
            printf("a   = %lx\n", a_bank);
            printf("exp = %lx\n", exp_bank);
            printf("res = %lx\n", res_bank);
            return 2;
        }
    }

    for (j = 0; j < BANK_TOTAL; j++) {
        fread(&a_bank, sizeof(uint64_t), 1, fbank);
        fread(&exp_bank, sizeof(uint64_t), 1, fbank);

        res_bank = modb(a_bank);
        if(res_bank != exp_bank) {
            printf("modb failed for these values:\n");
            printf("a   = %lx\n", a_bank);
            printf("exp = %lx\n", exp_bank);
            printf("res = %lx\n", res_bank);
            return 2;
        }
    }

    for (j = 0; j < BANK_TOTAL; j++) {
        fread(&a_bank, sizeof(uint64_t), 1, fbank);
        fread(&exp_bank, sizeof(uint64_t), 1, fbank);

        res_bank = FLT(a_bank);
        if(res_bank != exp_bank) {
            printf("FLT failed for these values:\n");
            printf("a   = %lx\n", a_bank);
            printf("exp = %lx\n", exp_bank);
            printf("res = %lx\n", res_bank);
            return 2;
        }

        res_bank = EEA(a_bank);
        if(res_bank != exp_bank) {
            printf("EEA failed for these values:\n");
            printf("a   = %lx\n", a_bank);
            printf("exp = %lx\n", exp_bank);
            printf("res = %lx\n", res_bank);
            return 2;
        }
    }

    printf("bank_passed = 1\n");

    return 0;
}

/* Output

*/
