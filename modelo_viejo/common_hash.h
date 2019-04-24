#ifndef HASH_H
#define HASH_H

#include <iostream>

class Hash {
    private:
 
    public:
        Hash();
        uint16_t calcularHash(const std::string &cadena);
        ~Hash();
};

#endif
