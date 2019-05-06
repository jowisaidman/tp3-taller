#include "server_comunicador.h"


Comunicador :: Comunicador(SocketConnect *socket,
    Indice *indice,Claves *claves) {
    this->socket = socket;
    this->indice = indice;
    this->claves = claves;
    termino = false;
}

Comunicador :: ~Comunicador() {
}

bool Comunicador :: terminoEjecucion() {
    return this->termino;
}

void Comunicador :: run() {
    ComandoServidor comando;

    comando.inciarModo(*socket,*indice,*claves);
    socket->cerrarConexion(); 
    delete socket;
    termino = true;
}
