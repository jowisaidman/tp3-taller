#ifndef ARCHIVO_CERTIFICADO_H
#define ARCHIVO_CERTIFICADO_H

#include <iostream>
#include <fstream>
#include <string>
#include "common_archivo.h"

class ArchivoCertificado : public Archivo {
    private:
        std::string certificado;
 
    public:
        using Archivo::Archivo;
        void parser();
        std::string getCertificado();
};

#endif
