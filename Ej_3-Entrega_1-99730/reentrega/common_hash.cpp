#include <string>
#include "common_hash.h"

Hash :: Hash() {
}

Hash :: ~Hash() {
}

uint16_t Hash :: calcularHash(const std::string &cadena) {
    uint16_t suma = 0;
    for (char c : cadena) {
        suma += (uint16_t) c;
    }
    return suma;
}
