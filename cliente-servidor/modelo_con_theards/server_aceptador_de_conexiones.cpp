#include "server_aceptador_de_conexiones.h"
#include <vector>

AcceptadorDeConexiones :: AcceptadorDeConexiones(SocketAccept &socket_aceptador,
    Indice &indice,Claves &claves) {
    this->continuar_ejecutando = true;
    this->socket_aceptador = &socket_aceptador;
    this->indice = &indice;
    this->claves = &claves;
}

AcceptadorDeConexiones :: ~AcceptadorDeConexiones() {
}

void AcceptadorDeConexiones :: finalizarEjecucion() {
    this->continuar_ejecutando = false;
    this->socket_aceptador->~SocketAccept(); //cehquear esto
}

void AcceptadorDeConexiones :: run() {
    std::vector<Comunicador*> comunicadores;
    //std::vector<Comunicador*> aux;
    while (this->continuar_ejecutando) {
        SocketConnect *socket_connect = socket_aceptador->acceptSocket();

        if (socket_connect == nullptr) {
            this->continuar_ejecutando = false;
        } else {
            comunicadores.push_back(new Comunicador(socket_connect,
            indice,claves));
            comunicadores.back()->start();
        }
        /*
        for (unsigned int i = 0; i < comunicadores.size(); ++i) {
            if (comunicadores[i]->terminoEjecucion()) {
                std::cout << "Rompe joineando\n";
                comunicadores[i]->join();
                delete comunicadores[i];
            } else {
                std::cout << "Rompe pusheando back\n";
                aux.push_back(comunicadores[i]);
            }

        }
        comunicadores = aux;*/
    }
    for (unsigned int i = 0; i<comunicadores.size(); i++) {
        comunicadores[i]->join();
        delete comunicadores[i];        
    }
}
