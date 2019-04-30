#include "server_cliente.h"
#include <string>

Cliente :: Cliente(std::string nombre,std::string exp,std::string mod,
    uint32_t indice) {
    this->nombre = nombre;
    this->exponente = exp;
    this->modulo = mod;
    this->indice = indice;
}

Cliente :: ~Cliente() {
    /*No hace nada*/
}

std::string Cliente :: getNombre() {
    return this->nombre;
}

std::string Cliente :: getModulo() {
    return this->modulo;
}

std::string Cliente :: getExponente() {
    return this->exponente;
}

uint32_t Cliente :: getIndice() {
    return this->indice;
}

bool Cliente :: operator==(const Cliente &otro) const {
    return this->nombre == otro.nombre;
}
