#include "rsa.h"
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
        std::cout << "El byte " << i << " es: " << (int)byte << std::endl;
        unsigned int result = 1;
        for (size_t j = 0; j<exp; j++) {
            result = (result * byte) % mod;
            std::cout <<"Result en paso "<< i << " es: "<<result << std::endl;
        }
        ret = ret + result*256*i + result*abs(i-1); 
    }
    std::cout << ret << std::endl;
    return ret;
}
