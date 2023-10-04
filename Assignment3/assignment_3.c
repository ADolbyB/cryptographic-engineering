#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EX1 1
#define EX2 1
#define EX3 1
#define EX4 1

#define ADD_LOOP(a, b, r)                               \
    carry = 0;                                          \
    for(i = 0; i < 15; i++) {                           \
        (r)[i]  = (a)[i] + (b)[i] + carry;              \
        carry = (r)[i] >> 16;                           \
        (r)[i] = (r)[i] & 0xffff;                       \
    }                                                   \
    (r)[i] = (a)[i] + (b)[i] + carry

#define SUB_LOOP(a, b, r)                               \
    carry = 0;                                          \
    for(i = 0; i < 15; i++) {                           \
        (r)[i]  = (a)[i] - (b)[i] - carry;              \
        carry = (r)[i] >> 63;                           \
        (r)[i] = (r)[i] & 0xffff;                       \
    }                                                   \
    (r)[i] = (a)[i] - (b)[i] - carry

#define ADD_MASK_LOOP(a, mask, b, r)                    \
    carry = 0;                                          \
    for(i = 0; i < 15; i++) {                           \
        (r)[i]  = (a)[i] + ((b)[i] & (mask)) + carry;   \
        carry = (r)[i] >> 16;                           \
        (r)[i] = (r)[i] & 0xffff;                       \
    }                                                   \
    (r)[i] = (a)[i] + ((b)[i] & (mask)) + carry

#define CARRY_PROP_LOOP(a, r)                           \
    carry = 0;                                          \
    for(i = 0; i < 15; i++) {                           \
        (r)[i]  = (a)[i] + carry;                       \
        carry = (r)[i] >> 16;                           \
        (r)[i] = (r)[i] & 0xffff;                       \
    }                                                   \
    (r)[i]  = (a)[i] + carry

#define ADD_MUL_DIGIT_LOOP(a, b, c0, r)                 \
    carry = 0;                                          \
    for(i = 0; i < 15; i++) {                           \
        (r)[i]  = (a)[i] + ((b)[i] * (c0)) + carry;     \
        carry = (r)[i] >> 16;                           \
        (r)[i] = (r)[i] & 0xffff;                       \
    }                                                   \
    (r)[i]  = (a)[i] + ((b)[i] * (c0)) + carry

typedef uint64_t bigint256[16]; //for operands
typedef uint64_t bigint512[32]; //for multiplication result

const bigint256 PRIME = {       // Value: 2^255 - 19
    0xffed, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7fff
};

// Print 256 bit number (Helper)
void bigint256_print(const bigint256 a) {
    int i;
    printf("{");
    for(i = 0; i < 15; i++)
        printf("0x%04lx,",a[i]);
    printf("0x%04lx}",a[i]);
}

//print 512 bit number (Helper)
void bigint512_print(const bigint512 a) {
    int i;
    printf("{");
    for(i = 0; i < 8; i++)
        printf("0x%09lx,",a[i]);
    printf("\n");
    for(i = 8; i < 16; i++)
        printf("0x%09lx,",a[i]);
    printf("\n");
    for(i = 16; i < 24; i++)
        printf("0x%09lx,",a[i]);
    printf("\n");
    for(i = 24; i < 31; i++)
        printf("0x%09lx,",a[i]);
    printf("0x%09lx}",a[i]);
}

// r = (a + b) % PRIME
void mod_add(bigint256 r, const bigint256 a, const bigint256 b) {
    int i;
    uint64_t carry, mask;

    // Write 1 here:                    // Modular addition
    ADD_LOOP(a, b, r);                  // r could be > p or < p
    SUB_LOOP(r, PRIME, r);              // We have -p < r < p
    mask = 0 - (r[15] >> 63);           // highest bit = 1 if the result is negative. Mask is either 0x000.. or all 0xFFF...
    ADD_MASK_LOOP(r, mask, PRIME, r);   // Finally we have (a + b) mod p

}

// r = (a - b) % PRIME
void mod_sub(bigint256 r, const bigint256 a, const bigint256 b) {
    int i;
    uint64_t carry, mask;

    // Write 2 here
}

void mul256(bigint512 r, const bigint256 a, const bigint256 b) {
    int i, j;
    // Initialize r with 0s
    memset(r, 0, 256);

    for(i = 0; i < 16; i++) {
        for(j = 0; j < 16; j++) {
            r[i + j] += a[j] * b[i];
        }
    }
}

// r = a % PRIME using pseudo mersenne reduction
void psu_reduce(bigint256 r, const bigint512 a) {
    int i;
    uint64_t carry, mask;

    // Write 3 here
}

void mod_mul(bigint256 r, const bigint256 a, const bigint256 b) {
    bigint512 t;
    mul256(t, a, b);
    psu_reduce(r, t);
}

void mod_sqr(bigint256 r, const bigint256 a) {
    bigint512 t;
    mul256(t, a, a);
    psu_reduce(r, t);
}

// r = (a^-1) % PRIME using pseudo mersenne reduction
void mod_inv(bigint256 r, const bigint256 a) {
    int i;
    bigint256 t;

    // Do NOT write into r until the very end. Otherwise, if you pass mod_inv(b, b) for example, 
    // it will output incorrect result. Use t as temporary variable.
    memcpy(t, a, sizeof(bigint256));

    // Write 4 here.

}

int main() {
    const int BANK_TOTAL = 1000;
    int i, pass;
    bigint256 a;
    bigint256 b;
    bigint512 c;    // for mult
    bigint256 exp1; // for add
    bigint256 exp2; // for sub
    bigint256 exp3; // for psu-reduce
    bigint256 exp4; // for inv
    bigint256 act;

    FILE *fbank = fopen("assignment_3_bank","r");

    if (fbank == NULL) {
        printf("'assignment_3_bank' file is missing. Please copy it to the same directory as where you execute the code.\n");
        return 1;
    }

    #if EX1
        printf("###############################\n");
        printf("Exercise 1:\n");
        printf("###############################\n");
        rewind(fbank);
        pass = 1;
        for (i = 0; i < BANK_TOTAL; i++) {
            fread(a, sizeof(bigint256), 1, fbank);
            fread(b, sizeof(bigint256), 1, fbank);
            fread(exp1, sizeof(bigint256), 1, fbank);
            fread(exp2, sizeof(bigint256), 1, fbank);
            fread(exp3, sizeof(bigint256), 1, fbank);
            fread(exp4, sizeof(bigint256), 1, fbank);

            mod_add(act, a, b);
            if(memcmp(act, exp1, sizeof(bigint256))) {
                printf("mod_add failed for these values:\n");
                printf("a   = "); bigint256_print(a); printf("\n");
                printf("b   = "); bigint256_print(b); printf("\n");
                printf("exp = "); bigint256_print(exp1); printf("\n");
                printf("res = "); bigint256_print(act); printf("\n");
                pass = 0;
                return 1;
            }
        }

        if(pass == 1) {
            printf("mod_add passed!\n");
        }
        printf("###############################\n\n");
    #endif

    #if EX2
        printf("###############################\n");
        printf("Exercise 2:\n");
        printf("###############################\n");
        rewind(fbank);
        pass = 1;
        for (i = 0; i < BANK_TOTAL; i++) {
            fread(a, sizeof(bigint256), 1, fbank);
            fread(b, sizeof(bigint256), 1, fbank);
            fread(exp1, sizeof(bigint256), 1, fbank);
            fread(exp2, sizeof(bigint256), 1, fbank);
            fread(exp3, sizeof(bigint256), 1, fbank);
            fread(exp4, sizeof(bigint256), 1, fbank);

            mod_sub(act, a, b);
            if(memcmp(act, exp2, sizeof(bigint256))) {
                printf("mod_sub failed for these values:\n");
                printf("a   = "); bigint256_print(a); printf("\n");
                printf("b   = "); bigint256_print(b); printf("\n");
                printf("exp = "); bigint256_print(exp2); printf("\n");
                printf("res = "); bigint256_print(act); printf("\n");
                pass = 0;
                return 1;
            }
        }

        if(pass == 1) {
            printf("mod_sub passed!\n");
        }
        printf("###############################\n\n");
    #endif
    

    #if EX3
        printf("###############################\n");
        printf("Exercise 3:\n");
        printf("###############################\n");
        rewind(fbank);
        pass = 1;
        for (i = 0; i < BANK_TOTAL; i++) {
            fread(a, sizeof(bigint256), 1, fbank);
            fread(b, sizeof(bigint256), 1, fbank);
            fread(exp1, sizeof(bigint256), 1, fbank);
            fread(exp2, sizeof(bigint256), 1, fbank);
            fread(exp3, sizeof(bigint256), 1, fbank);
            fread(exp4, sizeof(bigint256), 1, fbank);

            mul256(c, a, b);
            psu_reduce(act, c);
            if(memcmp(act, exp3, sizeof(bigint256))) {
                printf("psu_reduce failed for these values:\n");
                printf("a   = "); bigint256_print(a); printf("\n");
                printf("b   = "); bigint256_print(b); printf("\n");
                printf("a*b = "); bigint512_print(c); printf("\n");
                printf("exp = "); bigint256_print(exp3); printf("\n");
                printf("res = "); bigint256_print(act); printf("\n");
                pass = 0;
                return 1;
            }
        }

        if(pass == 1) {
            printf("psu_reduce passed!\n");
        }
        printf("###############################\n\n");
    #endif

    
    #if EX4
        printf("###############################\n");
        printf("Exercise 4:\n");
        printf("###############################\n");
        rewind(fbank);
        pass = 1;
        for (i = 0; i < BANK_TOTAL; i++) {
            fread(a, sizeof(bigint256), 1, fbank);
            fread(b, sizeof(bigint256), 1, fbank);
            fread(exp1, sizeof(bigint256), 1, fbank);
            fread(exp2, sizeof(bigint256), 1, fbank);
            fread(exp3, sizeof(bigint256), 1, fbank);
            fread(exp4, sizeof(bigint256), 1, fbank);

            mod_inv(act, a);
            if(memcmp(act, exp4, sizeof(bigint256))) {
                printf("mod_inv failed for these values:\n");
                printf("a   = "); bigint256_print(a); printf("\n");
                printf("b   = "); bigint256_print(b); printf("\n");
                printf("exp = "); bigint256_print(exp4); printf("\n");
                printf("res = "); bigint256_print(act); printf("\n");
                pass = 0;
                return 1;
            }
        }

        if(pass == 1) {
            printf("mod_inv passed!\n");
        }
        printf("###############################\n\n");
    #endif
    fclose(fbank);

    return 0;
}