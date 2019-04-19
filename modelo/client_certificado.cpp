#include <string>
#include "client_certificado.h"

/*void split(std::string buffer) {

}*/

void CertificadoCliente :: parser() {
    std::string buf;
    leerArchivo(buf);
    size_t pos = 0;
    int num_de_palabra = 0;
    std::string token;
    std::string delimitador = "\n";
    ingreso_fechas = false;
    //std::cout <<"entro al parser y el buffer es: "<< buf << std::endl;
    while (((pos = buf.find(delimitador)) != std::string::npos) && (num_de_palabra < 3)) {
        token = buf.substr(0, pos);
        //std::cout << "El token " << num_de_palabra << " es: " << token << std::endl;
        if (num_de_palabra == 0) nombre.assign(move(token));
        if (num_de_palabra == 1) fecha_inicial.assign(move(token));
        if (num_de_palabra == 2) fecha_final.assign(move(token));
        if (num_de_palabra>0) ingreso_fechas = true;
        buf.erase(0, pos + delimitador.length());
        num_de_palabra++;
    }    
}

std::string CertificadoCliente :: getNombre(){
    return nombre;
}

std::string CertificadoCliente :: getFechaInicial(){
    return fecha_inicial;
}

std::string CertificadoCliente :: getFechaFinal(){
    return fecha_final;
}

bool CertificadoCliente :: ingresoFechas() {
    return ingreso_fechas;
}
