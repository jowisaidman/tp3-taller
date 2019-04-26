#ifndef COMANDO_SERVIDOR_H
#define COMANDO_SERVIDOR_H
#include <iostream>
#include <string>
#include "common_protocolo.h" 
#include "common_socket_connect.h"
#include "server_claves.h"
#include "server_indice.h"
#include "common_certificado.h"

class ComandoServidor {
    private:
        Protocolo protocolo;
        bool comandoNew(SocketConnect &socket,Indice &indice,Claves &claves);
        bool comandoRevoke();
        bool comandoNewEnviarRespuesta(SocketConnect &socket,
            Certificado &certificado,const uint32_t &rsa);
        


    public:
        ComandoServidor();
        ~ComandoServidor();
        bool inciarModo(SocketConnect &socket,Indice &indice,Claves &claves);

};

#endif
