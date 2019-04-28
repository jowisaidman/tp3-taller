#include <string>
#include "server_comando.h"
#include "common_certificado.h"
#include "common_fecha.h"

ComandoServidor :: ComandoServidor() : protocolo() {
}

ComandoServidor :: ~ComandoServidor() {
    /*No hace nada*/
}

bool ComandoServidor :: verificarHash(Certificado &certificado,Indice &indice,
    Claves &claves, uint32_t huella) {

    std::string subject = certificado.getSubject();

    uint16_t mod_cliente = indice.getModuloCliente(subject); 
    uint8_t exp_cliente = indice.getExponenteCliente(subject);

    huella = certificado.calcularRsa(huella, exp_cliente, mod_cliente);
    
    uint16_t mod_servidor = claves.getModulo();
    uint8_t exp_servidor = claves.getExponentePrivado();

    huella = certificado.calcularRsa(huella, exp_servidor, mod_servidor);

    uint32_t hash = certificado.calcularHash();

    return hash == huella;    
}

bool ComandoServidor :: comandoRevoke(SocketConnect &socket,
    Indice &indice,Claves &claves) {
    uint32_t sn = 0;
    if (!this->protocolo.recibirInt32(&sn,socket)) return false;

    std::string subject;
    if (!this->protocolo.recibirString(subject,socket)) return false;

    std::string issuer;
    if (!this->protocolo.recibirString(issuer,socket)) return false;

    std::string fecha_incial;
    if (!this->protocolo.recibirString(fecha_incial,socket)) return false;

    std::string fecha_final;
    if (!this->protocolo.recibirString(fecha_final,socket)) return false;

    uint16_t modulo = -1;
    if (!this->protocolo.recibirInt16(&modulo,socket)) return false;

    uint8_t exponente = 0;
    if (!this->protocolo.recibirInt8(&exponente,socket)) return false;

    uint32_t huella = -1;
    if (!this->protocolo.recibirInt32(&huella,socket)) return false;

    Certificado certificado;
    certificado.setAtributos(sn,subject,fecha_incial,fecha_final,
      modulo,exponente);
    certificado.parser();

    uint8_t rta = 0;

    if (!indice.clientePerteneceAlIndice(subject)) {
        rta = 1;
        this->protocolo.enviarInt8(rta,socket);
        return false; 
    }
    if (!this->verificarHash(certificado,indice,claves,huella)) {
        rta = 2;
        this->protocolo.enviarInt8(rta,socket);
        indice.incrementarIndice();
        return false;
    } 
    indice.eliminarCliente(subject);
    this->protocolo.enviarInt8(rta,socket);
    return true;
}

bool ComandoServidor :: comandoNewEnviarRespuesta(SocketConnect &socket,
    Certificado &certificado,const uint32_t &rsa) {//falta try except
        
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

//falta una funcion que recibe los datos
bool ComandoServidor :: comandoNew(SocketConnect &socket,
    Indice &indice,Claves &claves) { 
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

    if (fecha_inicial == "") {
        Fecha fecha;
        fecha_inicial = fecha.getFechaActual();
        fecha_final = fecha.getFecha30DiasDespues();
    }

    uint32_t i = indice.getIndice();  
    Certificado certificado;
    certificado.setAtributos(i,subject,fecha_inicial,fecha_final,mod,exp);
    certificado.parser();

    uint16_t hash = certificado.calcularHash();
    uint32_t rsa = certificado.calcularRsa(hash,claves.getExponentePrivado(),
      claves.getModulo());
    rsa = certificado.calcularRsa(rsa,exp,mod);

    if (!this->comandoNewEnviarRespuesta(socket,certificado,rsa)) return false;
    
    uint8_t rta_del_cliente;
    if (!this->protocolo.recibirInt8(&rta_del_cliente,socket)) return false;
    if (rta_del_cliente != 0) {
        indice.incrementarIndice();
        return false;
    }
    indice.agregarNuevoCliente(subject,exp,mod);
    return true;
}

//este probablemente sea el metodo run
bool ComandoServidor :: inciarModo(SocketConnect &socket,
    Indice &indice,Claves &claves) {
    uint8_t modo = -1; //incio en modo invalido
    this->protocolo.recibirInt8(&modo,socket);
    if (modo == 0) {
        if (!this->comandoNew(socket,indice,claves)) return 1;
        return 0;
    } else if (modo == 1) {
        if (!this->comandoRevoke(socket,indice,claves)) return 1;
        return 0;
    } else {
        return 1;
    }
}
