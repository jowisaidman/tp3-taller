#ifndef SOCKET_CONNECT_H
#define SOCKET_CONNECT_H

#include <string>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

class SocketConnect {
    private:
        int s;
        int skt;
        struct addrinfo hints;
        struct addrinfo *result;
        struct addrinfo *ptr;
        void set_hints_socket();

    public:
        SocketConnect();
        SocketConnect(int socket);
        bool addrinfo(const char *hostn, const char *srvn);
        bool conectar();
        int recivirMensaje(std::string &buf);
        int enviarMensaje(std::string &msg);
        ~SocketConnect();
};

#endif