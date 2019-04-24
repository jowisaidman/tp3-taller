#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>
#include <fstream>
#include <string>

class Archivo {
    private:
        std::fstream archivo;
 
    public:
        Archivo(std::string &nombre_archivo);
        void leerArchivo(std::string &buf);
        virtual void parser() = 0;
        std::string escribirArchivo();        
        ~Archivo();
};

#endif
