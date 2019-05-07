#include <string>
#include "client_archivo_certificado.h"

void ArchivoCertificado :: parser() {
    std::string buf;
    leerArchivo(buf);
    this->certificado.assign(buf);
}

std::string ArchivoCertificado :: getCertificado(){
    return certificado;
}
