#ifndef COMUNICADOR_H
#define COMUNICADOR_H
#include "server_thread.h"
#include "server_indice.h"
#include "server_claves.h"
#include "common_socket_connect.h"
#include "server_comando.h"

class Comunicador : public Thread {
        private:
        SocketConnect *socket;
        Indice *indice;
        Claves *claves;
        bool termino;

        public:
        bool terminoEjecucion();
        Comunicador(SocketConnect *socket,
        Indice *indice,Claves *claves);
        ~Comunicador();
        virtual void run() override;
};

#endif
