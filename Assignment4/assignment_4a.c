/**
 * Joel Brigida
 * CDA-4321: Cryptographic Engineering
 * Assignment 4
 * Due 10/22/2023
 * 
 * To debug & enable all warnings at compilation time:
 * `gcc -g -Wall -Werror assignment_4a.c -o assignment_4a`
 * 
 * To set output to radix-16 (e.g. for `info locals` command)
 * `set output-radix 16`
 * 
*/

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EX1 1
#define EX2 1
#define EX3 1
#define EX4 1

#define REAL_RANDOM 0

FILE *fbank;

#if REAL_RANDOM
    #define RANDOM_DATA(ptr, size) \
    FILE *frandom = fopen("/dev/urandom", "r"); \
    fread((ptr), (size), 1, frandom); \
    fclose(frandom);
#else
    #define RANDOM_DATA(ptr, size) \
    fread((ptr), (size), 1, fbank);
#endif // REAL_RANDOM

typedef uint64_t bigint256[16]; // for operands
typedef uint64_t bigint512[32]; // for multiplication result

const bigint256 PRIME = {
    0xffed, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
    0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x7fff
};

// Print 256 bit number as 1 hex integer (Helper)
void print_hex256(const char *s, const bigint256 a) {
    int i;
    printf("%s", s);
    for(i = 15; i >= 0; i--)
        printf("%04lx", a[i]);
    printf("\n");
}

// Read a 256-bit hex integer into bigint256 (Helper). 1 indicates output valid. 0 not valid.
int read_hex256(const char *s, const char* a, bigint256 r) {
    static const long hextable[] = { 
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1, 0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,-1,10,11,12,13,14,15,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
    };
    
    int i, j;
    uint8_t c;
    long hex_value;
    
    if(strlen(a) != 64) {
        printf("Error: Length of %s is (%ld). It should be 64.\n", s, strlen(a));
        return 0;
    }

    memset(r, 0, sizeof(bigint256));

    for(i = 15; i >= 0; i--) {
        for (j = 3; j >= 0; j--) {
            c = *a++;
            hex_value = hextable[c];
            if (hex_value == -1) {
                printf("Error: Found invalid hex digit '%c'.\n", c);
                return 0;
            }
            r[i] += hex_value << (4*j);
        }
    }
    return 1;
}

// Print 256 bit number (Helper)
void bigint256_print(const bigint256 a) {
    int i;
    printf("{");
    for(i = 0; i < 15; i++)
        printf("0x%04lx,", a[i]);
    printf("0x%04lx}", a[i]);
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

// r = a * b using Karatsuba method
void mul(bigint512 r, const bigint256 a, const bigint256 b) {
    int i, j;

    //initialize arrays
    uint64_t ma[8];
    uint64_t mb[8];
    uint64_t z0[16] = {0};
    uint64_t z1[16] = {0};
    uint64_t z2[16] = {0};

    // Compute ma, mb
    for(i = 0; i < 8; i++) {
        ma[i] = a[i] + a[8 + i];
        mb[i] = b[i] + b[8 + i];
    }

    // Compute z0, z1, z2
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            z0[i + j] += a[i] * b[j];
            z1[i + j] += ma[i] * mb[j];
            z2[i + j] += a[8 + i] * b[8 + j];
        }
    }

    // Perform subtraction z1 = z1 - z0 - z2
    for(i = 0; i < 15; i++) // z0[15], z1[15], z2[15] are 0
        z1[i] = z1[i] - z0[i] - z2[i];

    // Implement final addition and put the result in r
    for(i = 0; i < 8; i++) {
        r[i] = z0[i];
        r[8 + i] = z0[8 + i] + z1[i];
        r[16 + i] = z1[8 + i] + z2[i];
        r[24 + i] = z2[8 + i];
    }
}

// r = a % PRIME using pseudo mersenne reduction
void psu_reduce(bigint256 r, const bigint512 a) {
    int i;
    uint64_t carry, mask;

    // First round of pseudo-mersenne with carry propagation
    // a[0 - 15] + 38 * a[16 - 31]
    carry = 0;
    for(i = 0; i < 15; i++) {
        r[i] = a[i] + 38 * a[16 + i] + carry;
        carry = r[i] >> 16;
        r[i] &= 0xffff;
    }
    r[i] = a[i] + 38 * a[16 + i] + carry;

    // Second round of pseudo-mersenne 
    r[0] = r[0] + 19 * (r[15] >> 15);
    r[15] &= 0x7fff; // Remove the high bits.

    // Perform carry propagation
    carry = 0;
    for(i = 0; i < 15; i++) {
        r[i] = r[i] + carry;
        carry = r[i] >> 16;
        r[i] &= 0xffff;
    }
    r[i] = r[i] + carry;

    // r = r mod p
    carry = 0;
    for(i = 0; i < 15; i++) {
        r[i] = r[i]- PRIME[i] - carry;
        carry = r[i] >> 63;
        r[i] &= 0xffff;
    }
    r[i] = r[i] - PRIME[i] - carry;

    mask = 0 - (r[15] >> 63);

    carry = 0;
    for(i = 0; i < 15; i++) {
        r[i] = r[i] + (mask & PRIME[i]) + carry;
        carry = r[i] >> 16;
        r[i] &= 0xffff;
    }
    r[i] = r[i] + (mask & PRIME[i]) + carry;
}

void mod_mul(bigint256 r, const bigint256 a, const bigint256 b){
    bigint512 t;
    mul(t, a, b);
    psu_reduce(r, t);
}

void mod_sqr(bigint256 r, const bigint256 a){
    bigint512 t;
    mul(t, a, a);
    psu_reduce(r, t);
}

// If option == 1, then r = b. If option == 0 then r = a.
void select_bigint256(bigint256 r, const bigint256 a, const bigint256 b, uint8_t option) {
    int i;                                      // for() loop
    uint64_t t;                                 // Temp variable
    uint64_t mask;

    mask = 0 - option;                          // mask is either 0 or 1. if 0, then 0 - option = 11111.... = -1

    for(i = 0; i < 16; i++) {
        t = a[i] ^ b[i];                        // a[i] XOR b[i]
        t = mask & t;                           // mask temp variable
        r[i] = a[i] ^ t;                        // write to r[i]
    }

}

// r = a^e mod p
void mod_exp(bigint256 r, const bigint256 a, const bigint256 e) {
    int i, j;                                   // one nested for() loop. one not a nested for() loop
    uint8_t bit;                                // bit becomes the 'option'
	bigint256 t, t2;                            // temp variables

    memcpy(t, a, sizeof(bigint256));            // Copy a to temp variable

    // 256-bit numbers: We only process 253 bits.
    // For index 15 only: need to set the MSB (bit 255) to 1.
    // For the MSB in index 15, we only care about 14/16 bits.
    // for(i = 13; i >= 0; i--) {               // process bits 0 - 14
    //     bit = e[15] >> i;                    // get the option to send to the select function
    //     bit &= 0x1;                          // make bit a single bit
    //     mod_sqr(t, t);
    //     mod_mul(t2, t, a);
    //     select_bigint256(t, t, t2, bit);
    // }

    // All other indices, we are processing all 16 bits.
    // for(i = 14; i >= 0; i--) {               // For index 0 - 14
    //     for(j = 15; j >= 0; j--) {           // Inner loop cycles through each bit in index
    //         bit = e[i] >> j;                 // get the option to send to the select function
    //         bit &= 0x1;                      // make bit a single bit
    //         mod_sqr(t, t);
    //         mod_mul(t2, t, a);
    //         select_bigint256(t, t, t2, bit);
    //     }
    // }

    // Optimized Solution: process 253 bits in a single loop
    for(i = 253; i >= 0; i--) {                 // 'i' is 8 bits: upper 4 is array index, lower 4 = bits in index
        bit = e[i >> 4] >> (i & 0xF);           // e[i >> 4]: upper 8 bits of i = array index 0 - 15
        bit &= 0x1;                             // (i & 0xF): lower bits of i = 16 total values: number of bits to shift.
        mod_sqr(t, t);                          // & 0x1 grabs a single bit of 'e'
        mod_mul(t2, t, a);                      // Square and multiply
        select_bigint256(t, t, t2, bit);        // Send to select function
    }

    memcpy(r, t, sizeof(bigint256));

}

// Generate secret key and public key.
void keyGen(bigint256 sk, bigint256 pk) {
    const bigint256 g = {                       // Generator
        0x4855, 0xafb3, 0xe21b, 0x24a6, 0x98f0, 0x02cd, 0xff08, 0xaaa1,
        0x379a, 0x461e, 0x08ea, 0xc8e8, 0xa1dd, 0x2cd7, 0x1d71, 0x4f62
    };
    int i;

    // Generate (random) secret key here
    RANDOM_DATA(sk, sizeof(bigint256));         // reads from the file & fills sk w/ random data.

    // RANDOM_DATA() fills each index of 'sk' with 64 bits. Need to mask to 16 bits only
    // Generate 3 masks: 
    sk[0] &= 0xFFF8;                            // CLEAR bits 0, 1, 2: & w/ 0xFFF8
    sk[15] |= 0x4000;                           // SET bit 254: | w/ 0x4000
    sk[15] &= 0x7FFF;                           // CLEAR bit 255: & w/ 0x7FFF
    
    for(i = 1; i < 15; i++) {
        sk[i] &= 0xFFFF;                        // Mask sk[1] to sk[14] to 16 bits
    }

    // Generate public key here: compute pk = g^{sk} mod PRIME
    mod_exp(pk, g, sk);

}

// Generate shared secret from the secret key & other party's public key
void sharedSecret(bigint256 ss, const bigint256 sk, const bigint256 pk) {

    // Compute shared secret: ss = pk^{sk} mod PRIME
    mod_exp(ss, pk, sk);

}

int main(int argc, char* argv[]) {
#if REAL_RANDOM
    int rtn;
    bigint256 sk;
    bigint256 pk;
    bigint256 ss;

    if (argc < 2) {
        printf("Arguments are required:\n");
        printf("For keygen: pass 'keygen'\n");
        printf("For shared: pass 'shared sk pk' where sk and pk are secret and public key in hex, respectively\n");
        return 1;
    }

    if(!strcmp(argv[1], "keygen")) {
        keyGen(sk, pk);
        print_hex256("sk = ", sk);
        print_hex256("pk = ", pk);
    } else if(!strcmp(argv[1], "shared")) {
        if(argc < 4) {
            printf("2 additional arguments are required:\n");
            printf("'sk pk' where sk and pk are secret and public key in hex, respectively\n");
            return 1;
        }
        rtn = read_hex256("sk", argv[2], sk);
        if (!rtn) {
            printf("sk = %s", argv[2]);
            return 1;
        }
        rtn = read_hex256("pk", argv[3], pk);
        if (!rtn) {
            printf("pk = %s", argv[3]);
            return 1;
        }

        sharedSecret(ss ,sk, pk);
        print_hex256("sk = ", sk);
        print_hex256("pk = ", pk);
        print_hex256("ss = ", ss);
    } else {
        printf("Invalid Argument '%s' : \n", argv[1]);
        printf("For keygen: pass 'keygen'\n");
        printf("For shared: pass 'shared sk pk' where sk and pk are secret and public key in hex, respectively\n");
        return 1;
    }
#else
    const int BANK_TOTAL = 1000;
    int i, pass;

    bigint256 a, b;
    uint8_t option = 0;
    bigint256 exp, act;

    bigint256 exp_sk, exp_pk, exp_ss;
    bigint256 act_sk, act_pk, act_ss;

    fbank = fopen("assignment_4a_bank","r");

    if (fbank == NULL) {
        printf("'assignment_4a_bank' file is missing. Please copy it to the same directory as where you execute the code.\n");
        return 1;
    }


#if EX1
    printf("###############################\n");
    printf("Exercise 1:\n");
    printf("###############################\n");
    rewind(fbank);
    fseek(fbank, 6*sizeof(bigint256)*BANK_TOTAL,SEEK_SET);
    pass = 1;
    for (i = 0; i < BANK_TOTAL; i++) {
        fread(a, sizeof(bigint256), 1, fbank);
        fread(b, sizeof(bigint256), 1, fbank);
        fread(&option, 1, 1, fbank);
        fread(exp, sizeof(bigint256), 1, fbank);

        select_bigint256(act, a, b, option);
        if(memcmp(act, exp, sizeof(bigint256))) {
            printf("select_bigint256 failed for these values:\n");
            printf("a   = "); bigint256_print(a); printf("\n");
            printf("b   = "); bigint256_print(b); printf("\n");
            printf("option = %d\n", option);
            printf("exp = "); bigint256_print(exp); printf("\n");
            printf("act = "); bigint256_print(act); printf("\n");
            pass = 0;
            break;
        }
    }

    if(pass == 1) {
        printf("select_bigint256 passed!\n");
    }
    printf("###############################\n\n");
#endif

#if EX2
    printf("###############################\n");
    printf("Exercise 2:\n");
    printf("###############################\n");
    rewind(fbank);
    fseek(fbank, (9*sizeof(bigint256)+1)*BANK_TOTAL,SEEK_SET);
    pass = 1;
    for (i = 0; i < BANK_TOTAL; i++) {
        fread(a, sizeof(bigint256), 1, fbank);
        fread(b, sizeof(bigint256), 1, fbank);
        fread(exp, sizeof(bigint256), 1, fbank);

        mod_exp(act, a, b);
        if(memcmp(act, exp, sizeof(bigint256))) {
            printf("mod_exp failed for these values:\n");
            printf("a   = "); bigint256_print(a); printf("\n");
            printf("b   = "); bigint256_print(b); printf("\n");
            printf("exp = "); bigint256_print(exp); printf("\n");
            printf("res = "); bigint256_print(act); printf("\n");
            pass = 0;
            break;
        }
    }

    if(pass == 1) {
        printf("mod_exp passed!\n");
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
        fread(exp_sk, sizeof(bigint256), 1, fbank);
        fread(exp_pk, sizeof(bigint256), 1, fbank);

        keyGen(act_sk, act_pk);
        if(memcmp(exp_sk, act_sk, sizeof(bigint256)) || memcmp(exp_pk, act_pk, sizeof(bigint256))) {
            printf("keyGen failed for these values:\n");
            printf("exp_sk   = "); bigint256_print(exp_sk); printf("\n");
            printf("exp_pk   = "); bigint256_print(exp_pk); printf("\n");
            printf("act_sk   = "); bigint256_print(act_sk); printf("\n");
            printf("act_pk   = "); bigint256_print(act_pk); printf("\n");
            pass = 0;
            break;
        }
    }

    if(pass == 1) {
        printf("keyGen passed!\n");
    }
    printf("###############################\n\n");
#endif

#if EX4
    printf("###############################\n");
    printf("Exercise 4:\n");
    printf("###############################\n");
    rewind(fbank);
    fseek(fbank, 3*sizeof(bigint256)*BANK_TOTAL,SEEK_SET);
    pass = 1;
    for (i = 0; i < BANK_TOTAL; i++) {
        fread(exp_sk, sizeof(bigint256), 1, fbank);
        fread(exp_pk, sizeof(bigint256), 1, fbank);
        fread(exp_ss, sizeof(bigint256), 1, fbank);

        sharedSecret(act_ss, exp_sk, exp_pk);
        if(memcmp(exp_ss, act_ss, sizeof(bigint256))) {
            printf("sharedSecret failed for these values:\n");
            printf("sk       = "); bigint256_print(exp_sk); printf("\n");
            printf("pk       = "); bigint256_print(exp_pk); printf("\n");
            printf("exp_ss   = "); bigint256_print(exp_ss); printf("\n");
            printf("act_ss   = "); bigint256_print(act_ss); printf("\n");
            pass = 0;
            break;
        }
    }

    if(pass == 1) {
        printf("sharedSecret passed!\n");
    }
    printf("###############################\n\n");
#endif

    fclose(fbank);
#endif // REAL_RANDOM

    return 0;
}

/**
 * Output From Assignment 4A:
 * 
 * 
*/