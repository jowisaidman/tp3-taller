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

        //Se encarga de agrega un nuevo cliente al mapa clientes
        void agregarCliente(std::string &nombre
        ,std::string exponente,std::string modulo);
        //Indica con un booleano si un cliente pertenece o no al map
        //indice. En caso de no perteneceser y que el booleano que 
        //recibe por parametro sea true, incrementa en uno el 
        //indice del archivo
        bool clientePerteneceAlIndice(const std::string &cliente,
            const bool modo_new); 

        //Elimina el cliente pasado por parametro del map clientes
        void eliminarCliente(const std::string &nombre); 

        //Indica con un booleano si el cliente pasado por paremetro
        //pertenece o no al map_de_espera
        bool clientePerteneceAEspera(const std::string &cliente);

    public:
        explicit Indice(std::string &nombre_archivo);
        ~Indice();

        //Lee el archivo 
        void leerArchivo();

        //Parsea el archivo de indice y los agrega al map clientes
        void parser(std::string &bf_aux,std::string &nombre_cliente
        ,std::string &exponente,bool &primer_palabra,
        bool &es_el_exp, bool &es_el_indice);

        //Escribe un archivo con la informacion que tiene el map
        //clientes
        void escribirArchivo();
        uint16_t getModuloCliente(const std::string &subject);
        uint8_t getExponenteCliente(const std::string &subject);

        //Agrega en caso que no pertenesca un cliente al 
        //mapa_de_espera
        bool agregarSiNoPertenece(std::string &nombre,
            uint8_t exponente,uint16_t modulo);

        //Elimina un cliente si pertenece al map de clientes
        bool eliminarSiPertenece(const std::string &nombre);

        //Agrega un cliente al mapa_de_espera
        void agregarAEspera(std::string &nombre,
            uint8_t exponente,uint16_t modulo);

        //Indica si un cliente pertence al map clientes
        void pasarClienteDeEsperaAIndice(std::string &nombre);

        //Elimina un cliente del mapa_de_espera
        void eliminarDeEspera(std::string &nombre);
        
        int getIndiceCliente(const std::string &nombre);
};

#endif
