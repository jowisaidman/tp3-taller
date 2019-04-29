#ifndef RSA_H
#define RSA_H

#include <iostream>

class Rsa {
    public:
        Rsa();
        uint32_t calcularRsa(
            const uint16_t &hash,
            const uint8_t &exp,
            const uint16_t &mod);
        ~Rsa();
};

#endif
