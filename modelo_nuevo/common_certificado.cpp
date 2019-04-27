#include <string>
#include <iomanip>
#include <sstream>
#include "common_certificado.h"
#include "common_fecha.h"
#include "common_hash.h"
#include "common_rsa.h"

Certificado :: Certificado(uint32_t sn,std::string &nombre,std::string &fecha_inicio
    ,std::string &fecha_fin,uint16_t mod, uint8_t exp) {
        serial_number = sn;
        subject = nombre;
        if (fecha_inicio == "") {
            Fecha fecha;
            fecha_inicial = fecha.getFechaActual();
            fecha_final = fecha.getFecha30DiasDespues();
        } else {
            fecha_inicial = fecha_inicio;
            fecha_final = fecha_fin;
        }
        modulo = mod;
        exponente = exp;
}

Certificado :: ~Certificado() {
    
}

std::string Certificado :: getHexadecimal(int largo,int n) {
    std::stringstream stream;
    stream << std::hex << n;
    std::string result( stream.str() );
    int tam = result.size();
    for (int i=0; i< largo-tam; i++) {
        result = "0"+result;
    }
    result = "(0x" + result + ")";
    return result;
}

void Certificado :: agregarSerialNumber() {
    certificado_completo += "serial number: "+ std::to_string(serial_number);
    std::string hexa = getHexadecimal(8,serial_number);
    certificado_completo += " "+hexa+"\n\t";
}

void Certificado :: agregarValidity() {
    certificado_completo += "validity:\n\t\tnot before: ";
    certificado_completo += fecha_inicial+"\n\t\t";
    certificado_completo += "not after: ";
    certificado_completo += fecha_final+"\n\t";
}

void Certificado :: agregegarPublicKeyInfo() {
    certificado_completo += "subject public key info:\n\t\t";
    certificado_completo += "modulus: " + std::to_string(modulo) + " ";
    std::string hexa_mod = getHexadecimal(4,modulo);
    certificado_completo += hexa_mod + "\n\t\t";
    certificado_completo += "exponent: " + std::to_string(exponente)+" ";
    std::string hexa_exp = getHexadecimal(2,exponente);
    certificado_completo += hexa_exp;
}

void Certificado :: parser() {
    certificado_completo = "certificate:\n\t";
    agregarSerialNumber();
    certificado_completo += "subject: "+subject+"\n\t";
    certificado_completo += "issuer: Taller de programacion 1\n\t";
    agregarValidity();
    agregegarPublicKeyInfo();
}

void Certificado :: imprmirCertificado() { //HAT QUE BORRAR ESTOO
    std::cout << certificado_completo << std::endl;
}

uint16_t Certificado :: calcularHash() {
    Hash hash;
    return hash.calcularHash(certificado_completo);
}

uint32_t Certificado :: calcularRsa(const uint32_t &hash ,const uint8_t &exp, const uint16_t &mod) {
    Rsa rsa;
    return rsa.calcularRsa(hash,exp,mod);    
}

uint32_t Certificado :: getSerialNumber() {
    return this->serial_number;
}
std::string Certificado :: getSubject() {
    return this->subject;
}
std::string Certificado :: getIssuer() {
    return "Taller de programacion 1";
}
std::string Certificado :: getFechaInicio() {
    return this->fecha_inicial;
}
std::string Certificado :: getFechaFin() {
    return this->fecha_final;
}
uint16_t Certificado :: getModulo() {
    return this->modulo;
}
uint8_t Certificado :: getExponente() {
    return this->exponente;
}

std::string Certificado :: getCertificado() {
    return this->certificado_completo;
}
