#ifndef SOCKET_ACCEPT
#define SOCKET_ACCEPT

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "common_socket_connect.h"

class SocketAccept {
    private:
        int s;
        int skt;
        int opt;
        struct addrinfo hints;
        struct addrinfo *ptr;
        void setHints(); 

    public:
        SocketAccept();
        ~SocketAccept();
        SocketConnect* acceptSocket();
        bool listenSocketAccept();
        bool bindSocketAccept();
        bool sktOpciones();
        bool addrinfo(char *srvn);
        bool sktSocketAccept();
        void cerrarSocket();
};

#endif
