#include <stdint.h>
#include "kpke.h"
#include "print_helpers.h"

#include "../kyber_src/params.h"
#include "../kyber_src/indcpa.h"

void kpke_keygen(uint8_t pk[KYBER_INDCPA_PUBLICKEYBYTES],
                    uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES])
{   
        print("\n---------K-PKE KeyGen---------");

        indcpa_keypair(pk, sk);

        print("Alice's public key:");
        print_hex_bytes(pk, KYBER_INDCPA_PUBLICKEYBYTES);
        print("Alice's secret key:");
        print_hex_bytes(sk, KYBER_INDCPA_SECRETKEYBYTES);
}

void kpke_encrypt(uint8_t c[KYBER_INDCPA_BYTES],
                const uint8_t m[KYBER_INDCPA_MSGBYTES],
                const uint8_t pk[KYBER_INDCPA_PUBLICKEYBYTES],
                const uint8_t r[KYBER_SYMBYTES])
{
    print("\n---------K-PKE Encrypt---------");

    indcpa_enc(c, m, pk, r);

    print("Bob's random:");
    print_hex_bytes(r, KYBER_SYMBYTES);
    print("Bob's message:");
    print_hex_bytes(m, KYBER_INDCPA_MSGBYTES);
    print("Bob's ciphertext:");
    print_hex_bytes(c, KYBER_CIPHERTEXTBYTES);
}

void kpke_decrypt(uint8_t m[KYBER_INDCPA_MSGBYTES],
                const uint8_t c[KYBER_INDCPA_BYTES],
                const uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES])
{
    print("\n---------K-PKE Decrypt---------");

    indcpa_dec(m, c, sk);
    print("Alice's decrypted message:");
    print_hex_bytes(m, KYBER_INDCPA_MSGBYTES);
}
