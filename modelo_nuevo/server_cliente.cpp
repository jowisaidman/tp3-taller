#include "server_cliente.h"

Cliente :: Cliente(std::string nombre_cliente,std::string exp,std::string mod) {
    nombre = nombre_cliente;
    exponente = exp;
    modulo = mod;
}

Cliente :: ~Cliente() {
    /*No hace nada*/
}

std::string Cliente :: getNombre() {
    return nombre;
}

std::string Cliente :: getModulo() {
    return modulo;
}

std::string Cliente :: getExponente() {
    return exponente;
}


/*void Cliente :: imprimirCliente() { //[HAY QUE BORRAR ESTA FUNCION]
    std::cout << nombre << std::endl;
    std::cout << exponente << std::endl;
    std::cout << modulo << std::endl;
}*/
