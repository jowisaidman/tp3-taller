#include <string>
#include <map>
#include <mutex>
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
        indice_archivo = stoi(bf_aux)-1;
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
    this->indice_archivo = 0;
    std::string nombre_cliente = "";
    while (archivo >> bf_aux) {
        parser(bf_aux,nombre_cliente,exponente,
        primer_palabra,es_el_exp,es_el_indice);
    }
}

void Indice :: eliminarCliente(const std::string &nombre) {
    Cliente *cliente = this->clientes[nombre];
    delete cliente;
    clientes.erase(nombre);
}

bool Indice :: clientePerteneceAlIndice(const std::string &cliente,
  const bool modo_new) {
    for (std::map<std::string,Cliente*>::iterator 
    it=clientes.begin(); it!=clientes.end(); ++it) {
        if (cliente == it->second->getNombre()) {
            return true;
        }
    }
    if (modo_new) this->indice_archivo++;
    return false;    
}

bool Indice :: eliminarSiPertenece(const std::string &nombre) {
    std::unique_lock<std::mutex> lck(m);
    if (this->clientePerteneceAlIndice(nombre,false)) {
        this->eliminarCliente(nombre);
        return true;
    }
    return false;
}

bool Indice :: clientePerteneceAEspera(const std::string &cliente) {
    for (std::map<std::string,Cliente*>::iterator 
    it=mapa_de_espera.begin(); it!=mapa_de_espera.end(); ++it) {
        if (cliente == it->second->getNombre()) {
            return true;
        }
    }
    return false;      
}

void Indice :: agregarAEspera(std::string &nombre,
    uint8_t exponente,uint16_t modulo) {
        std::string exp = std::to_string(exponente);
        std::string mod = std::to_string(modulo);
        Cliente *cliente = new Cliente(nombre,exp,mod,indice_archivo);
        this->mapa_de_espera.insert({nombre,cliente});
}

bool Indice :: agregarSiNoPertenece(std::string &nombre,
    uint8_t exponente,uint16_t modulo) {
        std::unique_lock<std::mutex> lck(m);
        if (!this->clientePerteneceAlIndice(nombre,true) &&
        !this->clientePerteneceAEspera(nombre)) {
            this->agregarAEspera(nombre,exponente,modulo);
            return true;
        }
        return false;
}

void Indice :: pasarClienteDeEsperaAIndice(std::string &nombre) {
    std::unique_lock<std::mutex> lck(m);
    Cliente *cliente = this->mapa_de_espera[nombre];
    this->clientes.insert({nombre,cliente});
    this->mapa_de_espera.erase(nombre);
}

void Indice :: eliminarDeEspera(std::string &nombre) {
    Cliente *cliente = this->mapa_de_espera[nombre];
    delete cliente;
    clientes.erase(nombre);    
}

void Indice :: agregarCliente(std::string &nombre,
  std::string exponente,std::string modulo) {
    Cliente *cliente = new Cliente(nombre,exponente,modulo,indice_archivo);
    this->clientes.insert({nombre,cliente});
}

void Indice :: escribirArchivo() {
    archivo.close();
    archivo.open(this->nombre_archivo, std::fstream::out | std::fstream::trunc);
    archivo << (this->indice_archivo+1) << '\n';
    for (std::map<std::string,Cliente*>::iterator 
    it=clientes.begin(); it!=clientes.end(); ++it) {
        archivo << it->second->getNombre()<< "; " << it->second->getExponente()
        << ' ' << it->second->getModulo() << '\n';
        delete it->second;
    }
}

uint16_t Indice :: getModuloCliente(const std::string &nombre) {
    if (this->clientePerteneceAlIndice(nombre,false)) {
        return (uint16_t)std::stoi(this->clientes[nombre]->getModulo());
    }
    return 0;
}

uint8_t Indice :: getExponenteCliente(const std::string &nombre) {
    if (this->clientePerteneceAlIndice(nombre,false)) {
        return (uint8_t)std::stoi(this->clientes[nombre]->getExponente());
    }
    return 0;
}

int Indice :: getIndiceCliente(const std::string &nombre) {
    return this->mapa_de_espera[nombre]->getIndice();
} 
