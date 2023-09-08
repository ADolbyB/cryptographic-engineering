/** 
 * Joel Brigida Z23521884
 * CDA4321-001: Cryptographic Engineering
 * 9/7/2016
 * Lab 1 Submission
*/


#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BENCH_LOOPS 1000

// a mod p1                                     // For Mersenne Primes of the form 2^n - 1
uint64_t modp1(uint64_t a) {                    // a = 2^30 - 18 = Number to be reduced
    const uint64_t p1 = 0x0001FFFF;             // p1 = 2^17 - 1 =  Modulus (Mersenne Prime)
    uint64_t r;

    r = (a >> 17) + (a & p1);                   // single step solution: add lower bits to upper bits.
    // r = (a >> 17);                           // 2 step solution: Retain upper 13 bits by shifting right 17
    // r = r + (a & p1);                        // Add lower & upper bits: mask 'a' to save lower 17 bits

    if(r >= p1) {                               // if r >= p1, then r >= modulus, so must be reduced
        r = r - p1;                             // r = result cannot be greater than the modulus
    }

    return r;
}

// a mod p2                                     // For Pseudo Marsenne primes of the form: 2^n - m.
uint64_t modp2(uint64_t a) {                    // a = 2^30 - 18: Number to be reduced
    const uint64_t p2 = 0x03FFFFFB;             // p2 = 2^26 - 5, Pseudo-Mersenne Prime: 2^n - m, m = 5
    uint64_t r;

    r = ((a >> 26) * 5) + (a & (p2 + 4));       // add upper and lower bits together
    // (a >> 26) * 5                            // shift 'a' right to save upper 4 bits of 'a', multiply by m = 5
    // a & (p2 + 4)                             // mask 'a' with p2 + 4 = 0x03FFFFF to preserve lower 26 bits

    while(r >= p2) {                            // r = result cannot be >= the modulus
        r = r - p2;                             // reduce r by the modulus amount
    }

    return r;
}

// a mod b                                      // Composite even power of 2
uint64_t modb(uint64_t a) {                     // a = 2^30 - 18 = Number to be reduced
    const uint64_t b = 0x00010000;              // b = 2^16 (even power of 2)
    uint64_t r;

    r = a & (b - 1);                            // Mask 'a' with (b - 1) = 0xFFFF to get the result

    return r;
}

// a^-1 mod p1 using FLT                        // a^(p1 - 2) == a^(-1) mod p
uint64_t FLT(uint64_t a) {                      // a = 51
    const uint64_t p1 = 0x0001FFFF;             // p1 = 2^17 - 1 = 0x1ffff = 131071 in decimal
    int i;
    uint64_t r = a;

    for(i = 0; i < (p1 - 3); i++) {             // p1 - 3 = 131068 in decimal
        r = modp1(r * a);                       // r = (r * a) % p1 : perform repeated multiplication for a^(p1 - 2)
    }                                           // mod operation every iteration to keep variable size within limits

    return r;
}

// a^-1 mod p1 using EEA
uint64_t EEA(uint64_t in) {
    const uint64_t p1 = 0x0001FFFF;
    int64_t a = p1;
    int64_t b = in;                             // b = 51 = 0x33

    int64_t u = 1;
    int64_t v = 0;
    int64_t d = a;
    int64_t v1 = 0;
    int64_t v3 = b;
    int64_t q, t1, t3;

    while(v3 != 0) {
        q = d / v3;                             // integer division
        t3 = d % v3;
        t1 = u - (q * v1);

        u = v1;
        d = v3;
        v1 = t1;
        v3 = t3;
    }

    v = (d - (a * u)) / b;                      // can have a negative result

    if(v < 0) {                                 // v can't be negative, or we have to make it positive
        v = v + a;                              // add modulus to 'v'
    }

    return v;
}

int main() {
    // ex.1a, 1b, 1c
    const uint64_t a1 = 0x3fffffee;
    printf("###############################\n");
    printf("Exercise 1:\n");
    printf("###############################\n");
    printf("a modulo p1 = %lx\n", modp1(a1));
    printf("a modulo p2 = %lx\n", modp2(a1));
    printf("a modulo b = %lx\n", modb(a1));
    printf("###############################\n\n");

    // ex.2a, 2b
    const uint64_t a2 = 51;
    printf("###############################\n");
    printf("Exercise 2:\n");
    printf("###############################\n");
    printf("Multiplication inverse of 51 using FLT = %lx\n", FLT(a2));
    printf("Multiplication inverse of 51 using EEA = %lx\n", EEA(a2));
    printf("###############################\n\n");

    // ex.3
    int i;
    unsigned long long cycles, cycles1, cycles2;
    FILE *urandom = fopen("/dev/urandom","r");  // for random input
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

    FILE *fbank = fopen("assignment_1_bank","r"); 

    if (fbank == NULL) {
        printf("'assignment1_bank' file is missing. Please copy it to the same directory as where you execute the code.\n");
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