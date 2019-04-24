#include "common_hash.h"

Hash :: Hash() {
}

Hash :: ~Hash() {
}

uint16_t Hash :: calcularHash(const std::string &cadena) {
    uint16_t suma = 0;
    for (char c : cadena) {
        suma += (uint16_t) c;
        std::cout << "Caracter: " << c << "\tValor: "<< (uint16_t)c << "\t Suma: " << suma <<std::endl;
    }
    return suma;
}
