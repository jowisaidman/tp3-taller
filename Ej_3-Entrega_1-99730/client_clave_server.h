#ifndef CLAVE_PUB_SERVER_H
#define CLAVE_PUB_SERVER_H

#include <iostream>
#include <string>
#include <fstream>
#include "common_archivo.h"

class ClavePublicaServer : public Archivo {
    private:
        uint16_t mod;
        uint8_t exp;

    public:
        using Archivo::Archivo;

        //Se encarga de parsear correctamente los datos 
        //del archivo leido.
        void parser();
        uint8_t getModulo();
        uint16_t getExponente();
};

#endif
