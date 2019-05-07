#ifndef ARCHIVO_CLAVE_CLIENTE_H
#define ARCHIVO_CLAVE_CLIENTE_H

#include <iostream>
#include <string>
#include <fstream>
#include "common_archivo.h"

class ClaveCliente : public Archivo {
    private:
        uint16_t mod;
        uint8_t exp_privado;
        uint8_t exp_publico;

    public:
        using Archivo::Archivo;

        //Se encarga de parsear correctamente los datos
        //del archivo leido
        void parser();
        
        uint8_t getExponentePublico();
        uint8_t getExponentePrivado();
        uint16_t getModulo();
};

#endif
