#include "common_rsa.h"
#include <cstdlib>

uint32_t Rsa :: calcularRsa(
    const uint16_t &hash,
    const uint8_t &exp,
    const uint16_t &mod){
    uint32_t ret = 0;
    for (size_t i = 0; i<4; i++) {
        uint32_t result = hash >> (i * 8) & 0xff;
        uint32_t base = result;
        for (size_t j = 1; j<exp; j++) {
            result = (result * base) % mod;
        }
        ret = ret + (result << (i*8)); 
    }
    return ret;
}
