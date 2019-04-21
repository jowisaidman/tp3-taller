#ifndef CLIENTE_S_H
#define CLIENTE_S_H

#include <iostream>
#include <string>

class Cliente { 
    private:
        std::string nombre;
        std::string modulo;
        std::string exponente;

    public:
        Cliente(std::string nombre,std::string exp,std::string mod);
        ~Cliente();
        //void imprimirCliente(); //HAY QUE BORRAR ESTA FUNCION
        std::string getExponente();
        std::string getNombre();
        std::string getModulo();
        //operador =

};


#endif
