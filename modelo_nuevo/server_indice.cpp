#include <string>
#include "server_cliente.h"
#include "server_indice.h"

Indice :: Indice(std::string &nombre_archivo) :
    archivo(nombre_archivo, std::fstream::in | std::fstream::out) ,clientes() {
        leerArchivo();
}

Indice :: ~Indice() {
    archivo.close();
}

void  Indice :: parser(std::string &bf_aux,std::string &nombre_cliente
    ,std::string &exponente,bool &primer_palabra, bool &es_el_exp
    , bool &es_el_indice, int &indice) {
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
            agregarCliente(nombre_cliente,exponente,bf_aux,indice);
            indice++;
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
    std::string nombre_cliente = "";
    std::string exponente;
    bool primer_palabra = true;
    bool es_el_exp = true;
    bool es_el_indice = true;
    int indice = 0;
    while (archivo >> bf_aux) {
        parser(bf_aux,nombre_cliente,exponente,primer_palabra,es_el_exp,es_el_indice,indice);
    }
}

void Indice :: decrementarIndice() {
    indice_archivo--;
}

void Indice :: incrementarIndice() {
    indice_archivo++;
}

uint32_t Indice :: getIndice() {
    return indice_archivo;
}

void Indice :: agregarCliente(std::string &nombre,
  std::string &exponente,std::string &modulo,int &indice) {
    //uint16_t mod = (uint16_t)stoi(modulo);
    //uint8_t exp = (uint8_t)stoi(exponente);
    Cliente *cliente = new Cliente(std::move(nombre),std::move(exponente),std::move(modulo));
    clientes[indice] = cliente;
}


/*void Indice :: imprimirClientes() { //HAY QUE BORRAR ESTA FUNCION
    for (int i = 0; i<indice_archivo-1 ;i++) {
        Cliente *cliente = clientes[i];
        cliente->imprimirCliente();
    }
}*/

void Indice :: escribirArchivo() {
    archivo << indice_archivo << '\n';
    for (std::map<int,Cliente*>::iterator it=clientes.begin(); it!=clientes.end(); ++it) {
        archivo << it->second->getNombre()<< "; " << it->second->getExponente()<< ' ' << it->second->getModulo() << '\n'; //NO ESTA ESCRIBIENDO
        delete it->second;
    }
    archivo << "OK" << '\n';
}