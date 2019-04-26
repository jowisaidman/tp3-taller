#ifndef INDICE_H
#define INDICE_H
#include <iostream>
#include <fstream>
#include <string>
#include <map> //ESTE MAP VA TENER QUE ESTAR PROTEGIDO
#include "common_archivo.h"
#include "server_cliente.h"

class Indice { //no hereda de archivo porque a diferencia de los demas parseo mientras leo
    private:
        std::string nombre_archivo;
        std::fstream archivo;
        std::map<std::string,Cliente*> clientes; //ESTE MAP VA TENER QUE ESTAR PROTEGIDO
        uint32_t indice_archivo;

        void agregarCliente(std::string &nombre
        ,std::string &exponente,std::string &modulo);
        void incrementarIndice();
        void decrementarIndice();

    public:
        Indice(std::string &nombre_archivo);
        ~Indice();
        void leerArchivo();
        void parser(std::string &bf_aux,std::string &nombre_cliente
        ,std::string &exponente,bool &primer_palabra,
        bool &es_el_exp, bool &es_el_indice);
        uint32_t getIndice();
        void agregarNuevoCliente(std::string &nombre
        ,uint8_t exponente,uint16_t modulo);
        bool clientePerteneceAlIndice(const std::string &cliente); 
        //quitarCliente(Cliente) ->hay que hacer delete
        void escribirArchivo();
        void imprimirClientes(); //[HYA QUE BORRAR ESTA FUNCION]
};


#endif