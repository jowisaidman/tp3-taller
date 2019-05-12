#ifndef HASH_H
#define HASH_H

#include <string>
#include <iostream>

class Hash {
    public:
        Hash() = default;
        //Recibe como parametro un string y calcula su hash.
        uint16_t calcularHash(const std::string &cadena);
        ~Hash() = default;
};

#endif
