#include "server_comando.h"
#include "common_certificado.h"

ComandoServidor :: ComandoServidor() : protocolo() {
}

ComandoServidor :: ~ComandoServidor() {
    /*No hace nada*/
}

bool ComandoServidor :: comandoRevoke() {
    return true;
}

bool ComandoServidor :: comandoNew(SocketConnect &socket,Indice &indice) {
    std::string subject;
    if (!protocolo.recibirString(subject,socket)) {
        std::cout << "se recibio mal nombre" << std::endl;
        return false; 
    }
    //std::cout << "Nombre:: " << subject << std::endl;

    uint16_t mod = -1;
    if (!this->protocolo.recibirInt16(&mod,socket)) {
        std::cout << "se recibio mal en modulo" << std::endl;
        return false; 
    }
    
    uint8_t exp = 0;
    if (!this->protocolo.recibirInt8(&exp,socket)) {
        std::cout << "se recibio mal en exponente" << std::endl;
        return false; 
    }
    
    std::string fecha_inicial;
    std::string fecha_final;
    if (!this->protocolo.recibirString(fecha_inicial,socket)) {
        std::cout << "Se recibio mal la fecha incial" << std::endl;
        return false;        
    }
    if (!this->protocolo.recibirString(fecha_final,socket)) {
        std::cout << "Se recibio mal la fecha final" << std::endl;
        return false;
    }

    std::cout << "Nombre:: " << subject << std::endl; //[BORRAR]
    std::cout << "Exponente: " << (int)exp << std::endl; //[BORRAR]
    std::cout << "Modulo: " << (int)mod << std::endl; //[BORRAR]
    std::cout << "Se recibio la fecha inicial: " << fecha_inicial << std::endl; //[BORRAR]
    std::cout << "Se recibio la fecha final: " << fecha_final << std::endl; //[BORRAR]
    std::cout << "Nombre:: " << subject << std::endl;
    if (fecha_inicial == "") std::cout << "NO HAY FECHAS" << std::endl; //aca creo fechas

    uint32_t i = indice.getIndice();
    Certificado certificado(i,subject,fecha_inicial,fecha_final,mod,exp);
    certificado.parser();
    uint16_t hash = certificado.calcularHash();
    std::cout << "El hash calculado es: " << hash << std::endl;
    return true;
}

bool ComandoServidor :: inciarModo(SocketConnect &socket,Indice &indice) {
    uint8_t modo; //incio en modo invalido
    this->protocolo.recibirInt8(&modo,socket);
    if (modo == 0) {
        if (!this->comandoNew(socket,indice)) return 1;
        return 0;
    } else if (modo == 1) {
        if (!this->comandoRevoke()) return 1;
        return 0;
    } else {
        return 1;
    }
}