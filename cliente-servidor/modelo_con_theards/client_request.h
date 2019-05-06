#ifndef REQUEST_CLIENTE_H
#define REQUEST_CLIENTE_H

#include <iostream>
#include <fstream>
#include <string>
#include "common_archivo.h"

class RequestCliente : public Archivo {
    private:
        std::string nombre;
        std::string fecha_inicial;
        std::string fecha_final;
        bool ingreso_fechas;
 
    public:
        using Archivo::Archivo;

        //Se encarga de parsear correctamente los datos
        //del archivo leido.
        void parser();
        bool ingresoFechas();
        std::string getNombre();
        std::string getFechaInicial();
        std::string getFechaFinal();
};

#endif
