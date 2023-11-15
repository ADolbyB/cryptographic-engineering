#include <stdint.h>
#include "../kyber_src/params.h"

void mlkem_keygen(uint8_t pk[KYBER_PUBLICKEYBYTES],
                    uint8_t sk[KYBER_SECRETKEYBYTES]);

void mlkem_encaps(uint8_t c[KYBER_CIPHERTEXTBYTES],
                    uint8_t ss[KYBER_SSBYTES],
                    uint8_t pk[KYBER_PUBLICKEYBYTES]);

void mlkem_decaps(uint8_t ss[KYBER_SSBYTES],
                    uint8_t c[KYBER_CIPHERTEXTBYTES],
                    uint8_t sk[KYBER_SECRETKEYBYTES]);

void kyber_kem_test(uint8_t ssA[KYBER_SSBYTES], uint8_t ssB[KYBER_SSBYTES]);