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

        //Recibe un Certificado, un Indice, Claves y un uint32_t y verifica
        //si el hash del certificado coincide con la huella dada. En caso que
        //coincidan devuelve 0, si no coinciden devuelve 2. En caso que no halla
        //podido extraer los datos necesarios del indice para calcular el hash 
        //devuelve 1.
        int verificarHash(Certificado &certificado,Indice &indice,
            Claves &claves,uint32_t huella);
        
    public:
        ComandoServidor();
        ~ComandoServidor();

        //Recibe como parametro un SocketConnect, un Indice y Claves. Espera
        //a recibir el modo en el que debe ser ejecutado el servidor (0 new o 
        //1 revoke).
        bool inciarModo(SocketConnect &socket,Indice &indice,Claves &claves);
};

#endif
