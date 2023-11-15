#include <stdint.h>
#include "../kyber_src/params.h"

void kpke_keygen(uint8_t pk[KYBER_INDCPA_PUBLICKEYBYTES],
                    uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES]);
void kpke_encrypt(uint8_t c[KYBER_INDCPA_BYTES],
                const uint8_t m[KYBER_INDCPA_MSGBYTES],
                const uint8_t pk[KYBER_INDCPA_PUBLICKEYBYTES],
                const uint8_t r[KYBER_SYMBYTES]);
void kpke_decrypt(uint8_t m[KYBER_INDCPA_MSGBYTES],
                const uint8_t c[KYBER_INDCPA_BYTES],
                const uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES]);

void kyber_pke_test(uint8_t rmA[KYBER_INDCPA_MSGBYTES],
                    uint8_t mB[KYBER_INDCPA_MSGBYTES]);