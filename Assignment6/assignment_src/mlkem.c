#include "print_helpers.h"
#include "mlkem.h"

#include "../kyber_src/params.h"
#include "../kyber_src/kem.h"

void mlkem_keygen(uint8_t pk[KYBER_PUBLICKEYBYTES],
                    uint8_t sk[KYBER_SECRETKEYBYTES])
{
        print("\n---------ML-KEM KeyGen---------");

        //Alice generates a public key
        crypto_kem_keypair(pk, sk);

        print("Alice's public key:");
        print_hex_bytes(pk, KYBER_PUBLICKEYBYTES);
        print("Alice's secret key:");
        print_hex_bytes(sk, KYBER_SECRETKEYBYTES);
}

void mlkem_encaps(uint8_t c[KYBER_CIPHERTEXTBYTES],
                    uint8_t ss[KYBER_SSBYTES],
                    uint8_t pk[KYBER_PUBLICKEYBYTES])
{
        print("\n---------ML-KEM Encaps---------");

        crypto_kem_enc(c, ss, pk);

        print("Bob's shared secret:");
        print_hex_bytes(ss, KYBER_SSBYTES);
        print("");
        print("Bob's ciphertext:");
        print_hex_bytes(c, KYBER_CIPHERTEXTBYTES);
}

void mlkem_decaps(uint8_t ss[KYBER_SSBYTES],
                    uint8_t c[KYBER_CIPHERTEXTBYTES],
                    uint8_t sk[KYBER_SECRETKEYBYTES])
{
    print("\n---------ML-KEM Decaps---------");

    crypto_kem_dec(ss, c, sk);

    print("Alice's shared secret:");
    print_hex_bytes(ss, KYBER_SSBYTES);
}