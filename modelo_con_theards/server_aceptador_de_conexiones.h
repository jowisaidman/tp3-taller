#ifndef ACEPTADOR_DE_CONEXIONES_H
#define ACEPTADOR_DE_CONEXIONES_H 
#include "server_socket_accept.h"
#include "server_comunicador.h"
#include "server_indice.h"
#include "server_claves.h"
#include <vector>


class AcceptadorDeConexiones : public Thread {
    private:
        SocketAccept *socket_aceptador;
        bool continuar_ejecutando;
        Indice *indice;
        Claves *claves;

    public:
        AcceptadorDeConexiones(SocketAccept &socket_aceptador,
        Indice &indice,Claves &claves);
        ~AcceptadorDeConexiones();
        virtual void run() override;
        void finalizarEjecucion();
};


#endif
