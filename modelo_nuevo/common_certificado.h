#ifndef CERTIFICADO_H
#define CERTIFICADO_H

#include <iostream>
#include <string>

class Certificado {
    private:
        uint32_t serial_number;
        std::string subject;
        std::string issuer;
        std::string fecha_inicial;
        std::string fecha_final;
        uint16_t modulo;
        uint8_t exponente;
        std::string certificado_completo;

        void agregarSerialNumber();
        std::string getHexadecimal(int largo,int n);
        void agregarValidity();
        void agregegarPublicKeyInfo(); 
 
    public:
        Certificado(uint32_t sn, std::string &nombre, std::string &fecha_inicio
         ,std::string &fecha_fin,uint16_t mod, uint8_t exp);
        ~Certificado();
        void parser();
        uint16_t calcularHash();
        void imprmirCertificado();
};

#endif