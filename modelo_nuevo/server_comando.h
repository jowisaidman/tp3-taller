#ifndef COMANDO_SERVIDOR_H
#define COMANDO_SERVIDOR_H
#include <iostream>
#include <string>
#include "common_protocolo.h" 
#include "common_socket_connect.h"
#include "server_claves.h"
#include "server_indice.h"

class ComandoServidor {
    private:
        Protocolo protocolo;
        bool comandoNew(SocketConnect &socket,Indice &indice);
        bool comandoRevoke();


    public:
        ComandoServidor();
        ~ComandoServidor();
        bool inciarModo(SocketConnect &socket,Indice &indice);

};

#endif
