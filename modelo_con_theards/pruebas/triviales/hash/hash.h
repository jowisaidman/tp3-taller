#ifndef HASH_H
#define HASH_H

#include <iostream>

class Hash {
    private:
 
    public:
        Hash();
        unsigned short int calcularHash(const std::string &cadena);
        ~Hash();
};

#endif
