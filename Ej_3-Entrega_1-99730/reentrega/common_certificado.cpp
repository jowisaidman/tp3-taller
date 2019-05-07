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

//void Certificado :: asignarCadena(size_t pos_inicial,size_t pos_final) {
//    
//} 
//void Certificado :: extraerDato(std::string inicio,puntero) {
//
//} 

//Estoy copiando codigo a morir, ver como pasar this-> como parametro;
void Certificado :: extraerSubject() {
    std::string subject = "subject: ";
    size_t pos_inicial = this->certificado_completo.find(subject) 
      +subject.size();
    std::string salto = "\n";
    size_t pos_final = this->certificado_completo.find(salto,pos_inicial);
    for (size_t i = pos_inicial; i<pos_final; i++) {
      this->subject += this->certificado_completo[i];
    }
}

void Certificado :: extraerSerialNumber() {
    std::string sn = "serial number: ";
    size_t pos_inicial = this->certificado_completo.find(sn) + sn.size();
    std::string parentesis = " (";
    size_t pos_final = this->certificado_completo.find(parentesis,pos_inicial);
    sn = "";
    for (size_t i = pos_inicial; i<pos_final; i++) {
      sn += this->certificado_completo[i];
    }
    this->serial_number = (uint32_t)std::stoi(sn);
}

void Certificado :: extraerIssuer() {
    std::string issuer = "issuer: ";
    size_t pos_inicial = this->certificado_completo.find(issuer) +issuer.size();
    std::string salto = "\n";
    size_t pos_final = this->certificado_completo.find(salto,pos_inicial);
    for (size_t i = pos_inicial; i<pos_final; i++) {
      this->issuer += this->certificado_completo[i];
    }
}

void Certificado :: extraerFechas() {
    std::string f_inicial = "not before: ";
    size_t pos_inicial = this->certificado_completo.find(f_inicial)
     +f_inicial.size();
    std::string salto = "\n";
    size_t pos_final = this->certificado_completo.find(salto,pos_inicial);
    for (size_t i = pos_inicial; i<pos_final; i++) {
      this->fecha_inicial += this->certificado_completo[i];
    }
    std::string f_final = "not after: ";
    pos_inicial = this->certificado_completo.find(f_final) +f_final.size();
    pos_final = this->certificado_completo.find(salto,pos_inicial);
    for (size_t i = pos_inicial; i<pos_final; i++) {
      this->fecha_final += this->certificado_completo[i];
    }
}

void Certificado :: extraerModulo() {
    std::string modulus = "modulus: ";
    size_t pos_inicial = this->certificado_completo.find(modulus)
     +modulus.size();
    std::string parentesis = " (";
    size_t pos_final = this->certificado_completo.find(parentesis,pos_inicial);
    std::string mod;
    for (size_t i = pos_inicial; i<pos_final; i++) {
      mod += this->certificado_completo[i];
    }
    this->modulo = (uint16_t)std::stoi(mod);
}

void Certificado :: extraerExponente() {
    std::string exponent = "exponent: ";
    size_t pos_inicial = this->certificado_completo.find(exponent)
     +exponent.size();
    std::string parentesis = " (";
    size_t pos_final = this->certificado_completo.find(parentesis,pos_inicial);
    std::string exp;
    for (size_t i = pos_inicial; i<pos_final; i++) {
      exp += this->certificado_completo[i];
    }
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
