#ifndef INDICE_H
#define INDICE_H
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <mutex>
#include "common_archivo.h"
#include "server_cliente.h"

class Indice {
    private:
        std::string nombre_archivo;
        std::fstream archivo;
        std::map<std::string,Cliente*> clientes; 
        std::map<std::string,Cliente*> mapa_de_espera; 
        std::mutex m;
        uint32_t indice_archivo;

        void agregarCliente(std::string &nombre
        ,std::string exponente,std::string modulo);
        bool clientePerteneceAlIndice(const std::string &cliente,
            const bool modo_new); 
        void eliminarCliente(const std::string &nombre); 
        bool clientePerteneceAEspera(const std::string &cliente);

    public:
        explicit Indice(std::string &nombre_archivo);
        ~Indice();
        void leerArchivo();
        void parser(std::string &bf_aux,std::string &nombre_cliente
        ,std::string &exponente,bool &primer_palabra,
        bool &es_el_exp, bool &es_el_indice);
        void escribirArchivo();
        uint16_t getModuloCliente(const std::string &subject);
        uint8_t getExponenteCliente(const std::string &subject);
        bool agregarSiNoPertenece(std::string &nombre,
            uint8_t exponente,uint16_t modulo);
        bool eliminarSiPertenece(const std::string &nombre);
        void agregarAEspera(std::string &nombre,
            uint8_t exponente,uint16_t modulo);
        void pasarClienteDeEsperaAIndice(std::string &nombre);
        void eliminarDeEspera(std::string &nombre);
        int getIndiceCliente(const std::string &nombre);
};

#endif
