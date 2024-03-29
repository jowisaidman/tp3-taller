#include <string>
#include <iomanip>
#include <sstream>
#include "common_certificado.h"
#include "common_fecha.h"
#include "common_hash.h"
#include "common_rsa.h"

void Certificado :: setAtributos(uint32_t sn,std::string 
    &nombre,std::string &fecha_inicio ,std::string &fecha_fin,
    uint16_t mod, uint8_t exp) {
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

std::string Certificado :: getHexadecimal(int largo,int n) {
    std::stringstream stream;
    stream << std::hex << n;
    std::string result(stream.str());
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

uint16_t Certificado :: calcularHash() {
    Hash hash;
    return hash.calcularHash(certificado_completo);
}

uint32_t Certificado :: calcularRsa(const uint32_t &hash ,
  const uint8_t &exp, const uint16_t &mod) {
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

void Certificado :: asignarCadena(size_t pos_inicial,
  size_t pos_final,std::string &cadena) {
    for (size_t i=pos_inicial; i< pos_final; i++) {
        cadena+= this->certificado_completo[i];
    }     
} 
void Certificado :: calcularPosicion(size_t &pos_inicial,size_t &pos_final,
    std::string &inicio, std::string &fin) {
        pos_inicial = this->certificado_completo.find(inicio)+inicio.size();;
        pos_final = this->certificado_completo.find(fin,pos_inicial); 
} 

void Certificado :: extraerSubject() {
    std::string subject = "subject: ";
    std::string salto = "\n";
    size_t pos_inicial(0);
    size_t pos_final(0);
    this->calcularPosicion(pos_inicial,pos_final,subject,salto);
    this->asignarCadena(pos_inicial,pos_final,this->subject);
}

void Certificado :: extraerSerialNumber() {
    std::string sn = "serial number: ";
    std::string parentesis = " (";
    size_t pos_inicial(0);
    size_t pos_final(0);
    this->calcularPosicion(pos_inicial,pos_final,sn,parentesis);
    sn = "";
    this->asignarCadena(pos_inicial,pos_final,sn);
    this->serial_number = (uint32_t)std::stoi(sn);
}

void Certificado :: extraerIssuer() {
    std::string issuer = "issuer: ";
    std::string salto = "\n";
    size_t pos_inicial(0);
    size_t pos_final(0);
    this->calcularPosicion(pos_inicial,pos_final,issuer,salto);
    this->asignarCadena(pos_inicial,pos_final,this->issuer);
}

void Certificado :: extraerFechas() {
    std::string f_inicial = "not before: ";
    std::string salto = "\n";
    size_t pos_inicial(0);
    size_t pos_final(0);
    this->calcularPosicion(pos_inicial,pos_final,f_inicial,salto);
    this->asignarCadena(pos_inicial,pos_final,this->fecha_inicial);
    std::string f_final = "not after: ";
    this->calcularPosicion(pos_inicial,pos_final,f_final,salto);
    this->asignarCadena(pos_inicial,pos_final,this->fecha_final);
}

void Certificado :: extraerModulo() {
    std::string modulus = "modulus: ";
    std::string parentesis = " (";
    size_t pos_inicial(0);
    size_t pos_final(0);
    this->calcularPosicion(pos_inicial,pos_final,modulus,parentesis);
    std::string mod;
    this->asignarCadena(pos_inicial,pos_final,mod);
    this->modulo = (uint16_t)std::stoi(mod);
}

void Certificado :: extraerExponente() {
    std::string exponent = "exponent: ";
    std::string parentesis = " (";
    size_t pos_inicial(0);
    size_t pos_final(0);
    this->calcularPosicion(pos_inicial,pos_final,exponent,parentesis);
    std::string exp;
    this->asignarCadena(pos_inicial,pos_final,exp);
    this->exponente = (uint16_t)std::stoi(exp);
} 

void Certificado :: setCertificado(std::string &certificado) {
    this->certificado_completo = certificado.substr(0,certificado.size()-1);
    this->extraerSerialNumber();
    this->extraerSubject();
    this->extraerIssuer();
    this->extraerFechas();
    this->extraerModulo();
    this->extraerExponente();
}
