#include <string>
#include "client_request.h"

void RequestCliente :: parser() {
    std::string buf;
    leerArchivo(buf);
    size_t pos = 0;
    int num_de_palabra = 0;
    std::string token;
    std::string delimitador = "\n";
    ingreso_fechas = false;
    while ((pos = buf.find(delimitador)) != std::string::npos) {
        token = buf.substr(0, pos);
        if (num_de_palabra == 0) nombre.assign(move(token));
        if (num_de_palabra == 1) fecha_inicial.assign(move(token));
        if (num_de_palabra == 2) fecha_final.assign(move(token));
        if (num_de_palabra>0) ingreso_fechas = true;
        buf.erase(0, pos + delimitador.length());
        num_de_palabra++;
    }    
}

std::string RequestCliente :: getNombre(){
    return nombre;
}

std::string RequestCliente :: getFechaInicial(){
    return fecha_inicial;
}

std::string RequestCliente :: getFechaFinal(){
    return fecha_final;
}

bool RequestCliente :: ingresoFechas() {
    return ingreso_fechas;
}
