#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <string.h>
#include <string>
#include <iostream>
#include "common_socket_connect.h"

class Protocolo {

    public:
        Protocolo();
        ~Protocolo();
        int enviarString(std::string &cadena,SocketConnect &socket);
        int recibirString(std::string &cadena,SocketConnect &socket);
        int enviarInt8(uint8_t valor,SocketConnect &socket);
        int enviarInt16(uint16_t valor,SocketConnect &socket);
        int enviarInt32(uint32_t valor,SocketConnect &socket);
        int recibirInt8(uint8_t *valor,SocketConnect &socket);
        int recibirInt16(uint16_t *valor,SocketConnect &socket);
        int recibirInt32(uint32_t *valor,SocketConnect &socket);
};

#endif
