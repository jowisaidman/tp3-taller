#ifndef SOCKET_CONNECT_H
#define SOCKET_CONNECT_H
#define RESPONSE_MAX_LEN 50

#include <string>
#include <stdio.h>
#include <string.h>
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
        explicit SocketConnect(int socket);
        bool addrinfo(const char *hostn, const char *srvn);
        bool conectar();

        //Cierra la conexion del socket.
        void cerrarConexion();
        ~SocketConnect() = default;
        //Recibe un string y un int.
        //Envia un mensaje al socket el cual esta conectado.
        int enviarMensaje(char *buf, int tam);

        //Recibe un string y un int.
        //Espera un mensaje del socket al cual esta conectado.
        int recibirMensaje(char *buf, int tam);

        //Devuelve un booleano indicando si el socket es valido
        bool isValid();

        SocketConnect& operator=(const SocketConnect&) = delete;
        SocketConnect(SocketConnect&& other);
        SocketConnect& operator=(SocketConnect&& other);
};

#endif
