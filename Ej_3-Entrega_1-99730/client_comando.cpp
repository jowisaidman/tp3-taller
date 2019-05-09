#include "client_comando.h"
#include <string>

ComandoCliente :: ComandoCliente(SocketConnect *socket) : protocolo(socket) {
}

bool ComandoCliente :: enviarModo(uint8_t m) {
    this->protocolo << m;
    return true;    
}

void ComandoCliente :: guardarCertificado(Certificado &certificado) {
    std::string nombre_archivo = certificado.getSubject() + ".cert";
    std::ofstream ofs(nombre_archivo, std::ofstream::out);
    ofs << certificado.getCertificado();
    ofs.close();
}

bool ComandoCliente :: comandoNewRecibirRespuesta(
    Protocolo &protocolo, ClavePublicaServer &clave_server,
    Claves &clave_cliete) { 
    uint8_t se_agrego = -1;
    this->protocolo >> se_agrego;

    if (se_agrego == 1) {
        std::cout << "Error: ya existe un certificado." << std::endl; 
        return false;
    }

    uint32_t sn=-1;
    this->protocolo >> sn;
    
    std::string subject;
    this->protocolo >> subject;

    std::string issuer;
    this->protocolo >> issuer;
    
    std::string fecha_inicial;
    this->protocolo >> fecha_inicial;

    std::string fecha_final;
    this->protocolo >> fecha_final;

    uint16_t mod(0);
    this->protocolo >> mod;

    uint8_t exp(0);
    this->protocolo >> exp;

    uint32_t huella(0);
    this->protocolo >> huella;

    Certificado certificado;
    certificado.setAtributos(sn,subject,fecha_inicial,fecha_final,mod,exp);
    certificado.parser();
    
    uint8_t exp_privado_cliente = clave_cliete.getExponentePrivado();
    uint8_t exp_servidor = clave_server.getExponente();
    uint16_t mod_servidor = clave_server.getModulo();
    uint32_t hash = certificado.calcularHash();
    uint32_t rsa = certificado.calcularRsa(huella,exp_privado_cliente,mod);
    rsa = certificado.calcularRsa(rsa,exp_servidor,mod_servidor);
    std::cout << "Huella del servidor: " << huella << std::endl;
    std::cout << "Hash del servidor: " << rsa << std::endl;
    std::cout << "Hash calculado: " << hash << std::endl;
    if (hash != rsa) {
        std::cout << "Error: los hashes no coinciden." << std::endl;
        return false;
    }
    this->guardarCertificado(certificado);
    return true;
}

bool ComandoCliente :: comandoNew(
    RequestCliente &request, Claves &claves_cliente, 
    ClavePublicaServer &clave_server) {
    uint8_t m = 0;
    if (!this->enviarModo(m)) return false;

    std::string nombre = request.getNombre();
    this->protocolo << nombre;

    uint16_t mod = claves_cliente.getModulo();
    this->protocolo << mod;       

    uint8_t exp_publico = claves_cliente.getExponentePublico();
    this->protocolo << exp_publico;

    if (request.ingresoFechas()) {
        std::string fecha_inicial = request.getFechaInicial();
        this->protocolo << fecha_inicial;

        std::string fecha_final = request.getFechaFinal();
        this->protocolo << fecha_final;
    }

    uint8_t rta;
    if (this->comandoNewRecibirRespuesta(protocolo,
      clave_server,claves_cliente)) {
        rta = 0;
    } else {  
        rta = 1;
    }

    this->protocolo << rta;

    return true;
}

uint8_t ComandoCliente :: respuestaDelServidor() {
    uint8_t rta = 3;//inicio invadio
    this->protocolo >> rta;
    return rta;
}


bool ComandoCliente :: comandoRevoke(
    ArchivoCertificado &arch_certificado, Claves &claves_cliente
    ,ClavePublicaServer &clave_server) {
    Certificado certificado;
    std::string certificado_texto = arch_certificado.getCertificado();
    certificado.setCertificado(certificado_texto);

    uint8_t m(1);
    this->protocolo << m;

    uint32_t sn = certificado.getSerialNumber();
    this->protocolo << sn;

    std::string subject = certificado.getSubject();
    this->protocolo << subject;

    std::string issuer = certificado.getIssuer();
    this->protocolo << issuer;

    std::string fecha_incial = certificado.getFechaInicio();
    this->protocolo << fecha_incial;

    std::string fecha_final= certificado.getFechaFin();
    this->protocolo << fecha_final;

    uint16_t modulo = certificado.getModulo();
    this->protocolo << modulo;

    uint8_t exponente = certificado.getExponente();
    this->protocolo << exponente;

    uint32_t hash = certificado.calcularHash(); 
    std::cout << "Hash calculado: " << hash << std::endl;
    uint8_t exp_cliente = claves_cliente.getExponentePrivado();
    uint16_t mod_cliente = claves_cliente.getModulo();
    uint32_t rsa = certificado.calcularRsa(hash,exp_cliente,mod_cliente);
    std::cout <<"Hash encriptado con la clave privada: "<< rsa << std::endl;
    uint8_t exp_servidor = clave_server.getExponente();
    uint16_t mod_servidor = clave_server.getModulo();
    rsa = certificado.calcularRsa(rsa,exp_servidor,mod_servidor);
    std::cout << "Huella enviada: " << rsa << std::endl;

    this->protocolo << rsa;

    uint8_t rta = this->respuestaDelServidor();
    if (rta == 1) {
        std::cout << "Error: usuario no registrado." << std::endl;
        return false;
    }

    if (rta == 2) {
        std::cout << "Error: los hashes no coinciden." << std::endl;
        return false;
    }

    return true;
}
