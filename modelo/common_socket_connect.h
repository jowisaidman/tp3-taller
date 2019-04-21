#ifndef SOCKET_CONNECT_H
#define SOCKET_CONNECT_H
#define RESPONSE_MAX_LEN 100

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
        SocketConnect(int socket);
        bool addrinfo(const char *hostn, const char *srvn);
        bool conectar();
        //int recibirMensaje(uint8_t *n,int tam);
        //int enviarMensaje(uint8_t *n,int tam);
        void cerrarConexion();
        ~SocketConnect();

        template <class T>
        int enviarMensaje(T msg, int tam) { //mas de 100 bytes no va enviar bien
            int total = 0,enviado = 0;
            bool el_socket_es_valido = true;
            char buf[RESPONSE_MAX_LEN];
            memcpy((T)buf,msg,tam);
            while (total < tam && el_socket_es_valido) {
                enviado = send(skt, &buf[total], tam-total, MSG_NOSIGNAL); 
                if (enviado <= 0) {
                    el_socket_es_valido = false;
                } else {
                    total += enviado;
                }
            }
            if (el_socket_es_valido) {
                return total;
            } else {
                return -1;
            }
        }

        template <class T>
        int recibirMensaje(T msg, int tam) {
            int total = 0,recivido = 0;
            bool el_socket_es_valido = true;
            char buf[RESPONSE_MAX_LEN];
            while (recivido < RESPONSE_MAX_LEN && el_socket_es_valido) {
                recivido = recv(skt, &buf[recivido], RESPONSE_MAX_LEN-recivido, MSG_NOSIGNAL);
                if (recivido <= 0) {
                    el_socket_es_valido = false;
                } else {
                    total += recivido;
                }
            }
            memcpy(msg,(uint8_t*)buf,tam);
            if (el_socket_es_valido) {
                return total;
            } else {
                return -1;
            }
        }

};

#endif
