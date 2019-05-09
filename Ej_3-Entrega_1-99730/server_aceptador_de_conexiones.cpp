#include "server_aceptador_de_conexiones.h"
#include <list>

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
    this->socket_aceptador->~SocketAccept();
}

void AcceptadorDeConexiones :: run() {
    std::list<Comunicador*> comunicadores;
    while (this->continuar_ejecutando) {
        SocketConnect *socket_connect = socket_aceptador->acceptSocket();
        if (!this->continuar_ejecutando) {
            delete socket_connect;
            continue;
        }

        if (socket_connect == nullptr) {
            this->continuar_ejecutando = false;
        } else {
            comunicadores.push_back(new Comunicador(socket_connect,
            indice,claves));
            comunicadores.back()->start();
        }

        for (auto i = comunicadores.begin(); i != comunicadores.end();) {
            if (!(*i)->terminoEjecucion()) {
                ++i;
            } else {
                (*i)->join();
                delete (*i);
                i = comunicadores.erase(i);
            }
        }
    }

    for (auto i = comunicadores.begin(); i!= comunicadores.end();) {
        (*i)->join();
        delete (*i);
        i = comunicadores.erase(i);
    }
}
