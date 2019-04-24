#include <string>
#include "common_archivo.h"

Archivo :: Archivo(std::string &nombre_archivo) :
    archivo(nombre_archivo, std::fstream::in | std::fstream::out) {
}

void Archivo :: leerArchivo(std::string &buf) {
    std::string buf_aux;
    while (std::getline(archivo, buf_aux)) {
        buf += buf_aux+"\n";
    }
} 

Archivo :: ~Archivo() {
    archivo.close();
}
