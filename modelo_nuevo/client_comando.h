#ifndef CLIENT_COMANDO_H
#define CLIENT_COMANDO_H
#include "common_protocolo.h"
#include "common_socket_connect.h"
#include "client_request.h"
#include "client_clave_server.h"
#include "client_clave.h"
#include <string>


class ComandoCliente {
    private:
        Protocolo protocolo;

        bool enviarModo(uint8_t m,SocketConnect &socket);
        //bool enviarNombre(std::string &nombre, SocketConnect &socket);

    public:
        ComandoCliente();
        ~ComandoCliente();
        bool comandoNew(SocketConnect &socket,RequestCliente &request
        , ClaveCliente &claves_cliente);
        bool comandoRevoke(SocketConnect &socket);
};

#endif
