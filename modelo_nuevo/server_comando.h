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
        bool comandoRevoke(SocketConnect &socket,Indice &indice,Claves &claves);
        bool comandoNewEnviarRespuesta(SocketConnect &socket,
            Certificado &certificado,const uint32_t &rsa);
        bool subjectPerteneceAlIndice(SocketConnect &socket,Indice &indice,
            const std::string &subject);
        bool verificarHash(Certificado &certificado,Indice &indice,
            Claves &claves,uint32_t huella);
        


    public:
        ComandoServidor();
        ~ComandoServidor();
        bool inciarModo(SocketConnect &socket,Indice &indice,Claves &claves);

};

#endif
