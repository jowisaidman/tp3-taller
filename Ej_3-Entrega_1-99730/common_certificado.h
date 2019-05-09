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
        void extraerSubject();
        void extraerSerialNumber();
        void extraerIssuer();
        void extraerFechas();
        void extraerModulo();
        void extraerExponente();  
        void asignarCadena(size_t pos_inicial,size_t pos_final,
          std::string &cadena);
        void calcularPosicion(size_t &pos_inicial,size_t &pos_final,
          std::string &inicio, std::string &fin);
 
    public:
        Certificado() = default;
        ~Certificado() = default;

        //Arma el certificado en el formato pedido. El certificado
        //debe tener todos los campos con informacion valida.
        void parser();

        //Calcula el hash de certificado_completo
        uint16_t calcularHash();

        //Calcula el rsa del certificado.
        uint32_t calcularRsa(const uint32_t &hash ,
          const uint8_t &exp, const uint16_t &mod);

        uint32_t getSerialNumber();
        std::string getSubject();
        std::string getIssuer();
        std::string getFechaInicio();
        std::string getFechaFin();
        uint16_t getModulo();
        uint8_t getExponente();
        std::string getCertificado();
        void setAtributos(uint32_t sn, std::string &nombre,
         std::string &fecha_inicio ,std::string &fecha_fin,
         uint16_t mod, uint8_t exp);
        void setCertificado(std::string &certificado);
};

#endif
