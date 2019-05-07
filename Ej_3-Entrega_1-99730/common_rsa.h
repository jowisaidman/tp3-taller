#ifndef RSA_H
#define RSA_H

#include <iostream>

class Rsa {
    public:
        Rsa();
        //Dado dos uint16_t y un uin8_t, encprita el uint16_t
        //con el exp y mod dados. 
        uint32_t calcularRsa(
            const uint16_t &hash,
            const uint8_t &exp,
            const uint16_t &mod);
        ~Rsa();
};

#endif
