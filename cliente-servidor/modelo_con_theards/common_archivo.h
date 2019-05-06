#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>
#include <fstream>
#include <string>

class Archivo {
    private:
        std::fstream archivo;
 
    public:
        explicit Archivo(std::string &nombre_archivo);

        //Se encarga de leer los datos dentro de archivo
        //y colocarlos en el buffer recibido por parametro.
        void leerArchivo(std::string &buf);
        virtual void parser() = 0;   
        ~Archivo();
};

#endif
