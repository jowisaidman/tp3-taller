#include <string>
#include <mutex>
#include "server_comando.h"
#include "common_certificado.h"
#include "common_fecha.h"

ComandoServidor :: ComandoServidor(SocketConnect *socket) : protocolo(socket) {
}

int ComandoServidor :: verificarHash(Certificado &certificado,Indice &indice,
    Claves &claves, uint32_t huella) {

    std::string subject = certificado.getSubject();
    uint16_t mod_cliente = indice.getModuloCliente(subject); 
    uint8_t exp_cliente = indice.getExponenteCliente(subject);

    if (mod_cliente == 0 && exp_cliente == 0) return 1;

    huella = certificado.calcularRsa(huella, exp_cliente, mod_cliente);
    
    uint16_t mod_servidor = claves.getModulo();
    uint8_t exp_servidor = claves.getExponentePrivado();

    huella = certificado.calcularRsa(huella, exp_servidor, mod_servidor);

    uint32_t hash = certificado.calcularHash();
    if (hash != huella) return 2;
    return 0;    
}

bool ComandoServidor :: comandoRevoke(
    Indice &indice,Claves &claves) {
    uint32_t sn = 0;
    this->protocolo >> sn;

    std::string subject;
    this->protocolo >> subject;

    std::string issuer;
    this->protocolo >> issuer;

    std::string fecha_incial;
    this->protocolo >> fecha_incial;

    std::string fecha_final;
    this->protocolo >> fecha_final;

    uint16_t modulo(0);
    this->protocolo >> modulo;

    uint8_t exponente(0);
    this->protocolo >> exponente;

    uint32_t huella(0);
    this->protocolo >> huella;

    Certificado certificado;
    certificado.setAtributos(sn,subject,fecha_incial,fecha_final,
      modulo,exponente);
    certificado.parser();

    uint8_t rta = 0;

    if (this->verificarHash(certificado,indice,claves,huella) == 2) {
        rta = 2;
        this->protocolo << rta;
        return false;
    }
    if (!indice.eliminarSiPertenece(subject)) {
        rta = 1;
        this->protocolo << rta;
        return false;         
    }
    this->protocolo << rta;
    return true;
}

bool ComandoServidor :: comandoNewEnviarRespuesta(
    Certificado &certificado,uint32_t &rsa) {
        
        uint32_t sn = certificado.getSerialNumber();
        this->protocolo << sn;

        std::string subject = certificado.getSubject();
        this->protocolo << subject;

        std::string issuer = certificado.getIssuer();
        this->protocolo << issuer;

        std::string f_inicial = certificado.getFechaInicio();
        this->protocolo << f_inicial;
        
        std::string f_final = certificado.getFechaFin();
        this->protocolo << f_final;
        
        uint16_t modulo = certificado.getModulo();
        this->protocolo << modulo;
        
        uint8_t exponente = certificado.getExponente();
        this->protocolo << exponente; 

        this->protocolo << rsa;

        return true;
}

bool ComandoServidor :: comandoNew(Indice &indice,Claves &claves) { 
    std::string subject;
    this->protocolo >> subject; 

    uint16_t mod(0);
    this->protocolo >> mod; 
    
    uint8_t exp(0);
    this->protocolo >> exp; 
    
    std::string fecha_inicial;
    this->protocolo >> fecha_inicial;   

    std::string fecha_final;
    this->protocolo >> fecha_final; 

    uint8_t rta;
    if (!indice.agregarSiNoPertenece(subject,exp,mod)) { 
        rta = 1;
        this->protocolo << rta;
        return false;
    } else {
        rta = 0;
        this->protocolo << rta;
    }
    if (fecha_inicial == "") {
        Fecha fecha;
        fecha_inicial = fecha.getFechaActual();
        fecha_final = fecha.getFecha30DiasDespues();
    }
    uint32_t i = indice.getIndiceCliente(subject);  
    Certificado certificado;
    certificado.setAtributos(i,subject,fecha_inicial,fecha_final,mod,exp);
    certificado.parser();

    uint16_t hash = certificado.calcularHash();
    uint32_t rsa = certificado.calcularRsa(hash,claves.getExponentePrivado(),
      claves.getModulo());
    rsa = certificado.calcularRsa(rsa,exp,mod);
    if (!this->comandoNewEnviarRespuesta(certificado,rsa)) return false;

    uint8_t rta_del_cliente;
    this->protocolo >> rta_del_cliente;
    if (rta_del_cliente != 0) {
        indice.eliminarDeEspera(subject);
        return false;
    }
    indice.pasarClienteDeEsperaAIndice(subject);
    return true;
}

bool ComandoServidor :: inciarModo(Indice &indice,Claves &claves) {
    uint8_t modo(2); //incio en modo invalido
    this->protocolo >> modo;
    if (modo == 0) {
        if (!this->comandoNew(indice,claves)) return 1;
        return 0;
    } else if (modo == 1) {
        if (!this->comandoRevoke(indice,claves)) return 1;
        return 0;
    } else {
        return 1;
    }
}
