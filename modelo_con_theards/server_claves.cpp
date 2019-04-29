#include <string>
#include "server_claves.h"

void Claves :: parser() {
    std::string buf;
    leerArchivo(buf);
    size_t pos = 0;
    int num_de_palabra = 0;
    std::string token;
    std::string delimitador = " ";
    while ((pos = buf.find(delimitador)) != std::string::npos) {
        token = buf.substr(0, pos);
        if (num_de_palabra == 0) exp_publico = (uint8_t)stoi(token);
        if (num_de_palabra == 1) exp_privado = (uint8_t)stoi(token);
        buf.erase(0, pos + delimitador.length());
        num_de_palabra++;
    }
    mod = (uint16_t)stoi(buf); 
}

uint8_t Claves :: getModulo() {
    return mod;
}

uint16_t Claves :: getExponentePrivado() {
    return exp_privado;
}

uint16_t Claves :: getExponentePublico() {
    return exp_publico;
}
