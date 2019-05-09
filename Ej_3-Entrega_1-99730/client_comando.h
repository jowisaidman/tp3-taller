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

        bool enviarModo(uint8_t m);
        bool comandoNewRecibirRespuesta(Protocolo
          &protocolo, ClavePublicaServer &clave_server,ClaveCliente 
          &clave_cliete);
        void guardarCertificado(Certificado &certificado);
        uint8_t respuestaDelServidor();


    public:
        explicit ComandoCliente(SocketConnect *socket);
        ~ComandoCliente() = default;

        //Recibe como parametro un SocketConnect, RequestCliente,
        //ClaveCliente y ClavePublicaServer. Se encarga de que se 
        //ejecute correctamente el comando new del cliente.
        bool comandoNew(RequestCliente &request
        , ClaveCliente &claves_cliente,ClavePublicaServer &clave_server);

        //Recibe como parametro un SocketConnect, RequestCliente,
        //ClaveCliente y ClavePublicaServer. Se encarga de que se 
        //ejecute correctamente el comando revoke del cliente.        
        bool comandoRevoke(ArchivoCertificado 
          &certificado,ClaveCliente &claves_cliente,ClavePublicaServer 
          &clave_server);
};

#endif
