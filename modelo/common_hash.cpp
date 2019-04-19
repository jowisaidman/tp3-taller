#include "common_hash.h"

Hash :: Hash() {
}

Hash :: ~Hash() {
}

unsigned short int Hash :: calcularHash(const std::string &cadena) {
    unsigned short int suma = 0;
    for (char c : cadena) {
        suma += (unsigned char) c;
    }
    return suma;
}
