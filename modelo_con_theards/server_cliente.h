#ifndef CLIENTE_S_H
#define CLIENTE_S_H

#include <iostream>
#include <string>

class Cliente { 
    private:
        std::string nombre;
        std::string modulo;
        std::string exponente;
        uint32_t indice;

    public:
        Cliente(std::string nombre,std::string exp,std::string mod,
            uint32_t indice);
        ~Cliente();
        std::string getExponente();
        std::string getNombre();
        std::string getModulo();
        uint32_t getIndice();
        bool operator==(const Cliente& otro) const;
};


#endif
