#ifndef CLIENT_COMANDO_H
#define CLIENT_COMANDO_H
#include "common_protocolo.h"
#include "common_certificado.h"
#include "common_socket_connect.h"
#include "client_request.h"
#include "client_clave_server.h"
#include "client_clave.h"
#include "client_archivo_certificado.h"
#include <string>


class ComandoCliente {
    private:
        Protocolo protocolo;

        bool enviarModo(uint8_t m,SocketConnect &socket);
        //bool enviarNombre(std::string &nombre, SocketConnect &socket);
        bool comandoNewRecibirRespuesta(SocketConnect &socket,Protocolo &protocolo,
        ClavePublicaServer &clave_server,ClaveCliente &clave_cliete);
        void guardarCertificado(Certificado &certificado);
        bool subjectEnviadoEsValido(SocketConnect &socket);


    public:
        ComandoCliente();
        ~ComandoCliente();
        bool comandoNew(SocketConnect &socket,RequestCliente &request
        , ClaveCliente &claves_cliente,ClavePublicaServer &clave_server);
        bool comandoRevoke(SocketConnect &socket,ArchivoCertificado &certificado,
         ClaveCliente &claves_cliente,ClavePublicaServer &clave_server);
};

#endif
