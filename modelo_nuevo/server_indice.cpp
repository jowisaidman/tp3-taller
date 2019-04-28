#include <string>
#include "server_cliente.h"
#include "server_indice.h"

Indice :: Indice(std::string &nombre_archivo) :
    archivo(nombre_archivo, std::fstream::in) ,clientes() {
        leerArchivo();
        this->nombre_archivo = nombre_archivo;
}

Indice :: ~Indice() {
    archivo.close();
}

void  Indice :: parser(std::string &bf_aux,std::string &nombre_cliente
    ,std::string &exponente,bool &primer_palabra, bool &es_el_exp
    , bool &es_el_indice) {
    if (es_el_indice) {
        indice_archivo = stoi(bf_aux);
        es_el_indice = false;
        return;
    }    
    if (bf_aux.back() == ';') {
        bf_aux.pop_back();
        nombre_cliente = nombre_cliente+" "+bf_aux;
        primer_palabra = true;
        return;
    }
    if (isdigit(bf_aux[0])) {
        if (es_el_exp) {
            exponente = bf_aux;
            es_el_exp = false;
        } else {
            agregarCliente(nombre_cliente,exponente,bf_aux);
            nombre_cliente = "";
            es_el_exp = true;
        }
        return;
    }
    if (!primer_palabra) {
        nombre_cliente = nombre_cliente + " " + bf_aux;
    } else {
        nombre_cliente = bf_aux;
        primer_palabra = false;
    }        
}

void Indice :: leerArchivo() {
    std::string bf_aux;
    std::string exponente;
    bool primer_palabra = true;
    bool es_el_exp = true;
    bool es_el_indice = true;
    std::string nombre_cliente = "";
    while (archivo >> bf_aux) {
        parser(bf_aux,nombre_cliente,exponente,primer_palabra,es_el_exp,es_el_indice);
    }
    if (primer_palabra) {
        this->indice_archivo = 1;
    }
}

void Indice :: incrementarIndice() {
    indice_archivo++;
}

uint32_t Indice :: getIndice() {
    return indice_archivo;
}

bool Indice :: clientePerteneceAlIndice(const std::string &cliente) {
    for (std::map<std::string,Cliente*>::iterator it=clientes.begin(); it!=clientes.end(); ++it) {
        if (cliente == it->second->getNombre()) {
            return true;
        }
    }
    return false;    
}

void Indice :: agregarCliente(std::string &nombre,
  std::string &exponente,std::string &modulo) {
    Cliente *cliente = new Cliente(nombre,exponente,modulo);
    this->clientes.insert({nombre,cliente});
}

void Indice :: agregarNuevoCliente(std::string &nombre,
    uint8_t exponente,uint16_t modulo) {
        std::string exp = std::to_string(exponente);
        std::string mod = std::to_string(modulo);
        this->agregarCliente(nombre,exp,mod);
        this->incrementarIndice();
}


/*void Indice :: imprimirClientes() { //HAY QUE BORRAR ESTA FUNCION
    for (std::map<std::string,Cliente*>::iterator it=clientes.begin(); it!=clientes.end(); ++it) {
        std::cout << it->second->getNombre()<< "; " << it->second->getExponente()<< ' ' << it->second->getModulo() << '\n';
    }
}*/

void Indice :: escribirArchivo() {
    archivo.close();
    archivo.open(this->nombre_archivo, std::fstream::out | std::fstream::trunc);
    archivo << indice_archivo << '\n';
    for (std::map<std::string,Cliente*>::iterator it=clientes.begin(); it!=clientes.end(); ++it) {
        archivo << it->second->getNombre()<< "; " << it->second->getExponente()<< ' ' << it->second->getModulo() << '\n';
        delete it->second;
    }
}

bool Indice :: eliminarCliente(const std::string &nombre) {
    if (this->clientePerteneceAlIndice(nombre)) {
        Cliente *cliente = this->clientes[nombre];
        delete cliente;
        clientes.erase(nombre);
        this->incrementarIndice();
        return true;
    }
    return false;
}

uint16_t Indice :: getModuloCliente(const std::string &subject) {
    return (uint16_t)std::stoi(this->clientes[subject]->getModulo());
}

uint8_t Indice :: getExponenteCliente(const std::string &subject) {
    return (uint8_t)std::stoi(this->clientes[subject]->getExponente());
}