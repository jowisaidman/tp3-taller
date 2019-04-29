#ifndef HASH_H
#define HASH_H

#include <string>
#include <iostream>

class Hash {
    public:
        Hash();
        uint16_t calcularHash(const std::string &cadena);
        ~Hash();
};

#endif
