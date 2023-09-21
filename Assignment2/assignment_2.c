/** 
 * Joel Brigida: Z23521884
 * CDA4321: Cryptographic Engineering
 * Dr. Reza Azarderaksh
 * Sept 13, 2023
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BENCH_LOOPS 10000

typedef uint64_t bigint256[16]; // for operands
typedef uint64_t bigint512[32]; // for multiplication result

const bigint256 a_exp  = {
    0x13ab,0xfdb2,0xd231,0xc1b3,0xb1d0,0x0867,0x14d8,0x0102,
    0x5c99,0x380b,0x658a,0xc279,0x9b97,0x02d1,0xda40,0x52fa
};
const bigint256 b_exp  = {
    0x79f5,0x5500,0xda19,0xed75,0xe4a0,0x48b6,0x695f,0x0ee7,
    0x6bee,0x52ca,0xdfa5,0xaeac,0x9d49,0x03f1,0xeb9b,0xc4a4
};

/* SageMath Code 1(a)

*/

// Update the sum here
const bigint256 add_exp = {0};


/* SageMath Code 2(a)

*/

// Update the difference here
const bigint256 sub_exp = {0};

const bigint512 mul_exp = { 
    0x0095ea5a7,0x07f63b45a,0x0c91ff598,0x18c71e6d8,0x244fa7f13,0x28f2eba45,0x263bdd778,0x205bef01a,
    0x18963b6a1,0x154ed05bf,0x1b81ca315,0x299508e38,0x36ba623b7,0x398b26e1e,0x3f4c64d71,0x3e45ae57b,
    0x3fb328c12,0x336181563,0x32fec692a,0x206882c5c,0x1c38aa08c,0x186558271,0x2039d413f,0x1c9efc02d,
    0x1c681de82,0x1e281238d,0x1e3534cea,0x0b07209d1,0x0cc4dc1fe,0x0f4028c5e,0x03fbc9028,0x000000000
};

// The following function get the time-stamp from processor, only works on Unix machines
int64_t cpucycles(void) {
    unsigned int hi, lo;

    asm volatile ("rdtsc\n\t" : "=a" (lo), "=d"(hi));
    return ((int64_t)lo) | (((int64_t)hi) << 32);
}

// Print 256 bit number (Helper)
void bigint256_print(const bigint256 a) {
    int i;
    printf("{");
    for(i = 0; i < 15; i++)
        printf("0x%04"PRIx64",",a[i]);
    printf("0x%04"PRIx64"}",a[i]);
}

//print 512 bit number (Helper)
void bigint512_print(const bigint512 a) {
    int i;
    printf("{");
    for(i = 0; i < 8; i++)
        printf("0x%09"PRIx64",",a[i]);
    printf("\n");
    for(i = 8; i < 16; i++)
        printf("0x%09"PRIx64",",a[i]);
    printf("\n");
    for(i = 16; i < 24; i++)
        printf("0x%09"PRIx64",",a[i]);
    printf("\n");
    for(i = 24; i < 31; i++)
        printf("0x%09"PRIx64",",a[i]);
    printf("0x%09"PRIx64"}",a[i]);
}

// r = a + b
void add256(bigint256 r, const bigint256 a, const bigint256 b) {
    int i;
    uint8_t carry = 0;

    // 1b:

}

// r = a - b
void sub256(bigint256 r, const bigint256 a, const bigint256 b) {
    int i;
    uint8_t borrow = 0;

    // 2b:

}

// r = a * b using schoolbook method
void schoolbook_mul256(bigint512 r, const bigint256 a, const bigint256 b) {
    int i, j;

    memset(r, 0, 256);                      // Initialize r with 0s
    // 3b:
    
}

// r = a * b using comba method
void comba_mul256(bigint512 r, const bigint256 a, const bigint256 b) {
    int i, j;

    // 3c:

}

// r = a * b using Karatsuba method
void karatsuba_mul256(bigint512 r, const bigint256 a, const bigint256 b) {
    int i, j;

    //initialize arrays
    uint64_t ma[8];
    uint64_t mb[8];
    uint64_t z0[16] = {0};
    uint64_t z1[16] = {0};
    uint64_t z2[16] = {0};

    // 3d:
    // Compute ma, mb

    // Compute z0, z1, z2

    // Perform subtraction z1 = z1 - z0 - z2

    // Implement final addition and put the result in r

}

int main() {
    int pass = 0;
    
    bigint256 add_res;
    bigint256 sub_res;
    bigint512 mul1_res;
    bigint512 mul2_res;
    bigint512 mul3_res;

    printf("a = "); bigint256_print(a_exp); printf("\n");
    printf("b = "); bigint256_print(b_exp); printf("\n\n");

    //ex.1
    printf("###############################\n");
    printf("Exercise 1:\n");
    printf("###############################\n");
    add256(add_res, a_exp, b_exp);
    pass = !memcmp(add_res, add_exp, sizeof(bigint256));
    printf("a + b: \n");
    printf("expect = "); bigint256_print(add_exp); printf("\n");
    printf("result = "); bigint256_print(add_res); printf("\n");
    printf("passed = %d\n\n", pass);

    // ex.2
    printf("###############################\n");
    printf("Exercise 2:\n");
    printf("###############################\n");
    sub256(sub_res, a_exp, b_exp);
    pass = !memcmp(sub_res, sub_exp, sizeof(bigint256));
    printf("a - b: \n");
    printf("expect = "); bigint256_print(sub_exp); printf("\n");
    printf("result = "); bigint256_print(sub_res); printf("\n");
    printf("passed = %d\n", pass);
    printf("###############################\n\n");

    // ex. 3
    printf("###############################\n");
    printf("Exercise 3:\n");
    printf("###############################\n");
    schoolbook_mul256(mul1_res, a_exp, b_exp);
    pass = !memcmp(mul1_res, mul_exp, sizeof(bigint512));
    printf("schoolbook: \n");
    printf("expect = "); bigint512_print(mul_exp); printf("\n");
    printf("result = "); bigint512_print(mul1_res); printf("\n");
    printf("passed = %d\n\n", pass);

    comba_mul256(mul2_res, a_exp, b_exp);
    pass = !memcmp(mul2_res, mul_exp, sizeof(bigint512));
    printf("comba: \n");
    printf("expect = "); bigint512_print(mul_exp); printf("\n");
    printf("result = "); bigint512_print(mul2_res); printf("\n");
    printf("passed = %d\n\n", pass);

    karatsuba_mul256(mul3_res, a_exp, b_exp);
    pass = !memcmp(mul3_res, mul_exp, sizeof(bigint512));
    printf("karatsuba: \n");
    printf("expect = "); bigint512_print(mul_exp); printf("\n");
    printf("result = "); bigint512_print(mul3_res); printf("\n");
    printf("passed = %d\n", pass);
    printf("###############################\n\n");

    //ex.4
    int i;
    bigint256 a_rand;
    bigint256 b_rand;
    bigint512 c_rand;
    unsigned long long cycles, cycles1, cycles2;
    FILE *urandom = fopen("/dev/urandom","r");  //for random input

    printf("###############################\n");
    printf("Exercise 4:\n");
    printf("###############################\n");

    cycles = 0;
    for (i = 0; i < BENCH_LOOPS; i++) {
        fread(a_rand, sizeof(bigint256), 1, urandom);
        fread(b_rand, sizeof(bigint256), 1, urandom);

        cycles1 = cpucycles();
        schoolbook_mul256(c_rand, a_rand, b_rand);
        cycles2 = cpucycles();
        cycles = cycles + (cycles2 - cycles1);
    }
    printf("Schoolbook runs in %10llu cycles\n", cycles/BENCH_LOOPS);

    cycles = 0;
    for (i = 0; i < BENCH_LOOPS; i++) {
        fread(a_rand, sizeof(bigint256), 1, urandom);
        fread(b_rand, sizeof(bigint256), 1, urandom);

        cycles1 = cpucycles();
        comba_mul256(c_rand, a_rand, b_rand);
        cycles2 = cpucycles();
        cycles = cycles + (cycles2 - cycles1);
    }
    printf("Comba runs in %10llu cycles\n", cycles/BENCH_LOOPS);

    cycles = 0;
    for (i = 0; i < BENCH_LOOPS; i++) {
        fread(a_rand, sizeof(bigint256), 1, urandom);
        fread(b_rand, sizeof(bigint256), 1, urandom);

        cycles1 = cpucycles();
        karatsuba_mul256(c_rand, a_rand, b_rand);
        cycles2 = cpucycles();
        cycles = cycles + (cycles2 - cycles1);
    }
    printf("Karatsuba runs in %10llu cycles\n", cycles/BENCH_LOOPS);

    fclose(urandom);
    printf("###############################\n\n");

    // Test bank:
    printf("###############################\n");
    printf("Test Bank:\n");
    printf("###############################\n");
    int j;
    bigint256 a_bank;
    bigint256 b_bank;
    bigint256 exp1_bank;
    bigint256 res1_bank;
    bigint256 exp2_bank;
    bigint256 res2_bank;
    bigint512 exp3_bank;
    bigint512 res3a_bank, res3b_bank, res3c_bank;
    const int BANK_TOTAL = 1000;

    FILE *fbank = fopen("assignment_2_bank","r"); 

    if (fbank == NULL) {
        printf("'assignment_2_bank' file is missing. Please copy it to the same directory as where you execute the code.\n");
        return 1;
    }

    // Test MUL bank
    for (j = 0; j < BANK_TOTAL; j++) {
        fread(a_bank, sizeof(bigint256), 1, fbank);
        fread(b_bank, sizeof(bigint256), 1, fbank);
        fread(exp1_bank, sizeof(bigint256), 1, fbank);
        fread(exp2_bank, sizeof(bigint256), 1, fbank);
        fread(exp3_bank, sizeof(bigint512), 1, fbank);

        add256(res1_bank, a_bank, b_bank);
        if(memcmp(res1_bank, exp1_bank, sizeof(bigint256))) {
            printf("add256 failed for these values:\n");
            printf("a = "); bigint256_print(a_bank); printf("\n");
            printf("b = "); bigint256_print(b_bank); printf("\n");
            printf("exp = "); bigint256_print(exp1_bank); printf("\n");
            printf("res = "); bigint256_print(res1_bank); printf("\n");
            return 2;
        }

        sub256(res2_bank, a_bank, b_bank);
        if(memcmp(res2_bank, exp2_bank, sizeof(bigint256))) {
            printf("sub256 failed for these values:\n");
            printf("a   = "); bigint256_print(a_bank); printf("\n");
            printf("b   = "); bigint256_print(b_bank); printf("\n");
            printf("exp = "); bigint256_print(exp2_bank); printf("\n");
            printf("res = "); bigint256_print(res2_bank); printf("\n");
            return 2;
        }

        schoolbook_mul256(res3a_bank, a_bank, b_bank);
        if(memcmp(res3a_bank, exp3_bank, sizeof(bigint512))) {
            printf("schoolbook_mul256 failed for these values:\n");
            printf("a   = "); bigint256_print(a_bank); printf("\n");
            printf("b   = "); bigint256_print(b_bank); printf("\n");
            printf("exp = "); bigint512_print(exp3_bank); printf("\n");
            printf("res = "); bigint512_print(res3a_bank); printf("\n");
            return 2;
        }

        comba_mul256(res3b_bank, a_bank, b_bank);
        if(memcmp(res3b_bank, exp3_bank, sizeof(bigint512))) {
            printf("comba_mul256 failed for these values:\n");
            printf("a   = "); bigint256_print(a_bank); printf("\n");
            printf("b   = "); bigint256_print(b_bank); printf("\n");
            printf("exp = "); bigint512_print(exp3_bank); printf("\n");
            printf("res = "); bigint512_print(res3b_bank); printf("\n");
            return 2;
        }

        karatsuba_mul256(res3c_bank, a_bank, b_bank);
        if(memcmp(res3c_bank, exp3_bank, sizeof(bigint512))) {
            printf("karatsuba_mul256 failed for these values:\n");
            printf("a   = "); bigint256_print(a_bank); printf("\n");
            printf("b   = "); bigint256_print(b_bank); printf("\n");
            printf("exp = "); bigint512_print(exp3_bank); printf("\n");
            printf("res = "); bigint512_print(res3c_bank); printf("\n");
            return 2;
        }
    }

    printf("bank_passed = 1\n");

    return 0;
}