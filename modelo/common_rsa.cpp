#include "common_rsa.h"
#include <cstdlib>

Rsa :: Rsa() {
}

Rsa :: ~Rsa() {
}

unsigned int Rsa :: calcularRsa(
    const unsigned short int &hash,
    const unsigned char &exp,
    const unsigned short int &mod){
    unsigned int ret = 0;
    for (size_t i = 0; i<2; i++) {
        unsigned char byte = hash >> (i * 8) & 0xff;
        unsigned int result = 1;
        for (size_t j = 0; j<exp; j++) {
            result = (result * byte) % mod;
        }
        ret = ret + result*256*i + result*abs(i-1); 
    }
    return ret;
}
