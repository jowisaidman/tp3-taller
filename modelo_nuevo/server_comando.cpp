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

bool ComandoServidor :: comandoNewEnviarRespuesta(SocketConnect &socket,
    Certificado &certificado,const uint32_t &rsa) {                 //falta try except
        
        uint32_t sn = certificado.getSerialNumber();
        if (!this->protocolo.enviarInt32(sn,socket)) return false;

        std::string subject = certificado.getSubject();
        if (!this->protocolo.enviarString(subject,socket)) return false;

        std::string issue = certificado.getIssuer();
        if (!this->protocolo.enviarString(issue,socket)) return false;

        std::string f_inicial = certificado.getFechaInicio();
        if (!this->protocolo.enviarString(f_inicial,socket)) return false;
        
        std::string f_final = certificado.getFechaFin();
        if (!this->protocolo.enviarString(f_final,socket)) return false;
        
        uint16_t modulo = certificado.getModulo();
        if (!this->protocolo.enviarInt16(modulo,socket)) return false;
        
        uint8_t exponente = certificado.getExponente();
        if (!this->protocolo.enviarInt8(exponente,socket)) return false; 

        if (!this->protocolo.enviarInt32(rsa,socket)) return false;

        return true;
}

bool ComandoServidor :: comandoNew(SocketConnect &socket,Indice &indice,Claves &claves) {  //falta una funcion que recibe los datos
    std::string subject;
    if (!protocolo.recibirString(subject,socket)) return false; 

    uint16_t mod = -1;
    if (!this->protocolo.recibirInt16(&mod,socket)) return false;
    
    uint8_t exp = 0;
    if (!this->protocolo.recibirInt8(&exp,socket)) {
        return false; 
    }
    
    std::string fecha_inicial;
    if (!this->protocolo.recibirString(fecha_inicial,socket)) return false;  

    std::string fecha_final;
    if (!this->protocolo.recibirString(fecha_final,socket)) return false;

    uint8_t rta;
    if (indice.clientePerteneceAlIndice(subject)) {
        rta = 1;
        this->protocolo.enviarInt8(rta,socket);
        return false;
    } else {
        rta = 0;
        this->protocolo.enviarInt8(rta,socket);
    }

    if (fecha_inicial == "") std::cout << "NO HAY FECHAS" << std::endl; //aca creo fechas

    uint32_t i = indice.getIndice();   //funcion aparte que se encargue de calcular todo
    Certificado certificado(i,subject,fecha_inicial,fecha_final,mod,exp);
    certificado.parser();
    uint16_t hash = certificado.calcularHash();
    uint32_t rsa = certificado.calcularRsa(hash,claves.getExponentePrivado(),claves.getModulo());
    rsa = certificado.calcularRsa(rsa,exp,mod);

    if (!this->comandoNewEnviarRespuesta(socket,certificado,rsa)) return false;
    
    uint8_t rta_del_cliente;
    if (!this->protocolo.recibirInt8(&rta_del_cliente,socket)) return false;
    if (rta != 0) return false;
    std::cout << "Antes de agregar: " << std::endl; 
    indice.imprimirClientes();
    indice.agregarNuevoCliente(subject,exp,mod);
    std::cout << "Despues de agregar: " << std::endl; 
    indice.imprimirClientes();

    return true;
}

bool ComandoServidor :: inciarModo(SocketConnect &socket,Indice &indice,Claves &claves) { //este probablemente sea el metodo run
    uint8_t modo; //incio en modo invalido
    this->protocolo.recibirInt8(&modo,socket);
    if (modo == 0) {
        if (!this->comandoNew(socket,indice,claves)) return 1;
        return 0;
    } else if (modo == 1) {
        if (!this->comandoRevoke()) return 1;
        return 0;
    } else {
        return 1;
    }
}