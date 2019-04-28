#include "client_comando.h"

ComandoCliente :: ComandoCliente() : protocolo() {
}


ComandoCliente :: ~ComandoCliente() {
    /*No hace nada*/
}

bool ComandoCliente :: enviarModo(uint8_t m,SocketConnect &socket) {
    if (this->protocolo.enviarInt8(m,socket) == -1) return false;
    return true;    
}

void ComandoCliente :: guardarCertificado(Certificado &certificado) {
    std::string nombre_archivo = certificado.getSubject() + ".cert";
    std::ofstream ofs(nombre_archivo, std::ofstream::out);
    ofs << certificado.getCertificado();
    ofs.close();
}

bool ComandoCliente :: comandoNewRecibirRespuesta(SocketConnect &socket,
    Protocolo &protocolo, ClavePublicaServer &clave_server,ClaveCliente &clave_cliete) { //falta un try except aca
    uint8_t se_agrego = -1;
    if(!this->protocolo.recibirInt8(&se_agrego, socket)) return false;

    if (se_agrego == 1) {
        std::cout << "Error: ya existe un certificado" << std::endl; 
        return false;
    }

    uint32_t sn=-1;
    if(!this->protocolo.recibirInt32(&sn, socket)) return false;
    
    std::string subject;
    if (!protocolo.recibirString(subject,socket)) return false; 

    std::string issuer;
    if (!protocolo.recibirString(issuer,socket)) return false; 
    
    std::string fecha_inicial;
    if (!this->protocolo.recibirString(fecha_inicial,socket)) return false;    

    std::string fecha_final;
    if (!this->protocolo.recibirString(fecha_final,socket)) return false;

    uint16_t mod = -1;
    if (!this->protocolo.recibirInt16(&mod,socket)) return false; 

    uint8_t exp = 0;
    if (!this->protocolo.recibirInt8(&exp,socket)) return false;

    uint32_t huella = -1;
    if (!this->protocolo.recibirInt32(&huella,socket)) return false; 

    Certificado certificado;
    certificado.setAtributos(sn,subject,fecha_inicial,fecha_final,mod,exp);
    certificado.parser();
    
    uint8_t exp_privado_cliente = clave_cliete.getExponentePrivado();
    uint8_t exp_servidor = clave_server.getExponente();
    uint16_t mod_servidor = clave_server.getModulo();

    uint32_t hash = certificado.calcularHash();
    uint32_t rsa = certificado.calcularRsa(huella,exp_privado_cliente,mod);
    rsa = certificado.calcularRsa(rsa,exp_servidor,mod_servidor); //falta verificar que coicidan e imprmir, se deberia hacer funcion aparte (y usarla para revoke)
    if (hash != rsa) {
        std::cout << "Error: los hashes no coinciden." << std::endl;
        return false;
    }
    std::cout << "Huella del servidor: " << huella << std::endl;
    std::cout << "Hash del servidor: " << hash << std::endl;
    std::cout << "Hash calculado " << rsa << std::endl;
    this->guardarCertificado(certificado);
    return true;
}

bool ComandoCliente :: comandoNew(SocketConnect &socket ,RequestCliente &request, //falta una funcion que envie los datos y tenga un try except
     ClaveCliente &claves_cliente, ClavePublicaServer &clave_server) {
    uint8_t m = 0;
    if(!this->enviarModo(m,socket)) return false;

    std::string nombre = request.getNombre();
    if (protocolo.enviarString(nombre,socket) == -1) return false; //falta funcion string que envie de a pedazos y otra que reciba de a pedazos dentro de protocolo

    uint16_t mod = claves_cliente.getModulo();
    if (protocolo.enviarInt16(mod,socket) == -1) return false;       

    uint8_t exp_publico = claves_cliente.getExponentePublico();
    if (protocolo.enviarInt8(exp_publico,socket) == -1) return false;

    if (request.ingresoFechas()) {
        std::string fecha_inicial = request.getFechaInicial();
        if (protocolo.enviarString(fecha_inicial,socket) == -1) return false;       

        std::string fecha_final = request.getFechaFinal();
        if (protocolo.enviarString(fecha_final,socket) == -1) return false;
    }

    uint8_t rta;
    if (this->comandoNewRecibirRespuesta(socket,protocolo,clave_server,claves_cliente)) {
        rta = 0;
    } else {  
        rta = 1;
    }
    this->protocolo.enviarInt8(rta,socket);

    return true;
}

uint8_t ComandoCliente :: respuestaDelServidor(SocketConnect &socket) {
    uint8_t rta = 3;//inicio invadio
    if (!this->protocolo.recibirInt8(&rta,socket)) return false;
    return rta;
}


bool ComandoCliente :: comandoRevoke(SocketConnect &socket,ArchivoCertificado &arch_certificado,
    ClaveCliente &claves_cliente,ClavePublicaServer &clave_server) {

    Certificado certificado;
    std::string certificado_texto = arch_certificado.getCertificado();
    certificado.setCertificado(certificado_texto);

    uint8_t m = 1;//aca falta un try except
    if (!this->enviarModo(m,socket)) return false;

    uint32_t sn = certificado.getSerialNumber();
    if (!this->protocolo.enviarInt32(sn,socket)) return false;

    std::string subject = certificado.getSubject();
    if (!this->protocolo.enviarString(subject,socket)) return false;

    if (this->respuestaDelServidor(socket) == 1) {
        std::cout << "Error: usuario no registrado." << std::endl;
        return false;
    }

    std::string issuer = certificado.getIssuer();
    if (!this->protocolo.enviarString(issuer,socket)) return false;

    std::string fecha_incial = certificado.getFechaInicio();
    if (!this->protocolo.enviarString(fecha_incial,socket)) return false;

    std::string fecha_final= certificado.getFechaFin();
    if (!this->protocolo.enviarString(fecha_final,socket)) return false;

    uint16_t modulo = certificado.getModulo();
    if (!this->protocolo.enviarInt16(modulo,socket)) return false;

    uint8_t exponente = certificado.getExponente();
    if (!this->protocolo.enviarInt8(exponente,socket)) return false;

    uint32_t hash = certificado.calcularHash(); //Esto se deberia hacer en una funcion aparte
    std::cout << "Hash calculado: " << hash << std::endl;
    uint8_t exp_cliente = claves_cliente.getExponentePrivado();
    uint16_t mod_cliente = claves_cliente.getModulo();
    uint32_t rsa = certificado.calcularRsa(hash,exp_cliente,mod_cliente);
    std::cout << "Hash encriptado con la clave prívada: " << rsa << std::endl;
    uint8_t exp_servidor = clave_server.getExponente();
    uint16_t mod_servidor = clave_server.getModulo();
    rsa = certificado.calcularRsa(rsa,exp_servidor,mod_servidor);
    std::cout << "Huella enviada: " << rsa << std::endl;

    if (!this->protocolo.enviarInt32(rsa,socket)) return false;

    if (this->respuestaDelServidor(socket) == 2) {
        std::cout << "Error: los hashes no coinciden." << std::endl;
        return false;
    }

    return true;
}
