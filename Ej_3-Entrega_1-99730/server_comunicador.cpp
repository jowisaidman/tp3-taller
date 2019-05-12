#include "server_comunicador.h"


Comunicador :: Comunicador(SocketConnect socket,
    Indice *indice,Claves *claves) {
    this->socket = std::move(socket);
    this->indice = indice;
    this->claves = claves;
    termino = false;
}

bool Comunicador :: terminoEjecucion() {
    return this->termino;
}

void Comunicador :: run() {
    try {
        ComandoServidor comando(&socket);
        comando.inciarModo(*indice,*claves);
        socket.cerrarConexion(); 
        termino = true;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Ocurrio un error desconocido" << std::endl;
    }
}
