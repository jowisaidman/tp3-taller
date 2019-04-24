#include <string>
#include "client_clave_server.h"


void ClavePublicaServer :: parser() {
    std::string buf;
    leerArchivo(buf);
    size_t pos = 0;
    int num_de_palabra = 0;
    std::string token;
    std::string delimitador = " ";
    while ((pos = buf.find(delimitador)) != std::string::npos) {
        token = buf.substr(0, pos);
        if (num_de_palabra == 0) exp = (uint8_t)stoi(token);
        if (num_de_palabra == 1) mod = (uint16_t)stoi(token);
        buf.erase(0, pos + delimitador.length());
        num_de_palabra++;
    }    
}

uint8_t ClavePublicaServer :: getModulo(){
    return mod;
}

uint16_t ClavePublicaServer :: getExponente(){
    return exp;
}
