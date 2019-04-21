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
        std::fstream archivo;
        std::map<int,Cliente*> clientes; //ESTE MAP VA TENER QUE ESTAR PROTEGIDO
        int indice_archivo;

    public:
        Indice(std::string &nombre_archivo);
        ~Indice();
        void leerArchivo();
        void parser(std::string &bf_aux,std::string &nombre_cliente
        ,std::string &exponente,bool &primer_palabra,
        bool &es_el_exp, bool &es_el_indice,int &indice);
        void incrementarIndice();
        void decrementarIndice();
        //buscarCliente(Cliente)
        void agregarCliente(std::string &nombre
        ,std::string &exponente,std::string &modulo,int &indice);
        //quitarCliente(Cliente) ->hay que hacer delete
        void escribirArchivo();
        //void imprimirClientes(); //[HYA QUE BORRAR ESTA FUNCION]
};


#endif