#ifndef INDICE_H
#define INDICE_H
#include <iostream>
#include <fstream>
#include <string>
#include <map> //ESTE MAP VA TENER QUE ESTAR PROTEGIDO
#include "common_archivo.h"
#include "server_cliente.h"

class Indice {
    private:
        std::string nombre_archivo;
        std::fstream archivo;
        std::map<std::string,Cliente*> clientes; 
        uint32_t indice_archivo;

        //Recibe como parametro tres cadenas y agrega al map
        //un cliente. Puede ser llamado desde el parser o
        //cuando un nuevo cliente es registrado.
        void agregarCliente(std::string &nombre
        ,std::string &exponente,std::string &modulo);

    public:
        explicit Indice(std::string &nombre_archivo);
        ~Indice();

        //Lee el archivo que contiene los datos del indice.
        void leerArchivo();

        //Se encarga de parsear el archivo que contiene los datos
        //del indice. Se encarga de que se agreguen todos los 
        //clientes ya registrados correctamente.
        void parser(std::string &bf_aux,std::string &nombre_cliente
        ,std::string &exponente,bool &primer_palabra,
        bool &es_el_exp, bool &es_el_indice);

        uint32_t getIndice();

        //Agrega un nuevo cliente al map.
        void agregarNuevoCliente(std::string &nombre
        ,uint8_t exponente,uint16_t modulo);

        //Recibe como parametro un string representando el nombre
        //de un usuario y devuelve un booleano indicando si 
        //esta o no en el map.
        bool clientePerteneceAlIndice(const std::string &cliente);

        //Recibe como parametro un string representando el nombre
        //de un usuario y en caso que este en el map lo elimna.
        //Devuelve un booleano indicando si tuvo exito. 
        bool eliminarCliente(const std::string &nombre);

        //Escribe en un archivo los datos que se encuentran en 
        //el map. 
        void escribirArchivo();
        
        uint16_t getModuloCliente(const std::string &subject);
        uint8_t getExponenteCliente(const std::string &subject);

        //Incrementa en uno indice_archivo.
        void incrementarIndice();
};

#endif
