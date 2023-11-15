/**
 * Joel Brigida
 * CDA-4321: Cryptographic Engineering
 * Assignment 6: Kyber / ML-KEM Post-Quantum Algorithms
*/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "assignment_src/kpke.h"
#include "assignment_src/mlkem.h"
#include "assignment_src/print_helpers.h"

#include "kyber_src/params.h"
#include "kyber_src/randombytes.h"

/*  #################################
*   TO COMPILE USING GCC USE COMMAND
*   gcc kyber_src/*.c assignment_src/*.c  assignment_6a.c -o assignment_6a.out && ./assignment_6a.out 
*   #################################
*/ 


void kyber_pke_test(uint8_t mA[KYBER_INDCPA_MSGBYTES],
                    uint8_t mB[KYBER_INDCPA_MSGBYTES]) 
{
        uint8_t pkA[KYBER_INDCPA_PUBLICKEYBYTES];
        uint8_t skA[KYBER_INDCPA_SECRETKEYBYTES];
        uint8_t ctB[KYBER_INDCPA_BYTES];
        uint8_t rB[KYBER_SYMBYTES];

        // Use: kpke_keygen(), kpke_encrypt(), kpke_decrypt(), randombytes()
        // See: assignment_src/kpke.h, assignment_src/kpke.c and kyber_src/randombytes.h

        // 1.a Here


        // 1.b Here


        // 1.c Here
}



void kyber_kem_test(uint8_t ssA[KYBER_SSBYTES], uint8_t ssB[KYBER_SSBYTES]) {
        uint8_t pkA[KYBER_PUBLICKEYBYTES];
        uint8_t skA[KYBER_SECRETKEYBYTES];
        uint8_t ctB[KYBER_CIPHERTEXTBYTES];

        // Use: mlkem_keygen(), mlkem_encaps(), mlkem_decaps()
        // See: assignment_src/mlkem.h and assignment_src/mlkem.c

        // 2.a Here


        // 2.b Here


        // 2.C Here
    }

int main(void) {

    uint8_t mA[KYBER_INDCPA_MSGBYTES];
    uint8_t mB[KYBER_INDCPA_MSGBYTES];
    uint8_t ssA[KYBER_SSBYTES];
    uint8_t ssB[KYBER_SSBYTES];

    kyber_pke_test(mA, mB);
    kyber_kem_test(ssA, ssB);

    print("\n################################");
    print("###### K-PKE FINAL RESULT ######");
    print("################################\n");

    print("Alice's message:");
    print_hex_bytes(mA, KYBER_INDCPA_MSGBYTES);
    print("Bob's message:");
    print_hex_bytes(mB, KYBER_INDCPA_MSGBYTES);

    if(memcmp(mA, mB, KYBER_INDCPA_MSGBYTES)) {
        print("!!! ERROR !!!");
        print("Alice's message DOES NOT match Bob's!");
        print("");
        return 1;

    } else {
        print("");
        print("Alice's message matches Bob's!");
        print("");
    }

    print("\n#################################");
    print("###### ML-KEM FINAL RESULT ######");
    print("#################################\n");

    print("Alice's shared secret:");
    print_hex_bytes(ssA, KYBER_SSBYTES);
    print("Bob's shared secret:");
    print_hex_bytes(ssB, KYBER_SSBYTES);

    if(memcmp(ssA, ssB, KYBER_SSBYTES)) {
        print("!!! ERROR !!!");
        print("Alice's shared secret DOES NOT match Bob's!");
        print("");
        return 1;

    } else {
        print("");
        print("Alice's shared secret matches Bob's!");
        print("");
    }

    return 0;

}