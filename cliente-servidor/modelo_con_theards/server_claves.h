#ifndef CLAVES_H
#define CLAVES_H
#include <iostream>
#include <fstream>
#include <string>
#include "common_archivo.h"

class Claves : public Archivo {
    private:
        uint8_t exp_privado;
        uint8_t exp_publico;
        uint16_t mod;

    public:
        using Archivo::Archivo;

        //Se encarga de parsear correctamente los datos del 
        //archivo leido
        void parser();
        uint8_t getModulo();
        uint16_t getExponentePrivado();
        uint16_t getExponentePublico();
};

#endif
