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
    try {
        ComandoServidor comando(socket);
        comando.inciarModo(*indice,*claves);
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    socket->cerrarConexion(); 
    delete socket;
    termino = true;
}
