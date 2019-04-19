#ifndef CERTIFICADO_CLIENTE_H
#define CERTIFICADO_CLIENTE_H

#include <iostream>
#include <fstream>
#include <string>
#include "common_archivo.h"

class CertificadoCliente : public Archivo {
    private:
        std::string nombre;
        std::string fecha_inicial;
        std::string fecha_final;
        bool ingreso_fechas;
 
    public:
        using Archivo::Archivo;
        void parser();
        bool ingresoFechas();
        std::string getNombre();
        std::string getFechaInicial();
        std::string getFechaFinal();
};

#endif
