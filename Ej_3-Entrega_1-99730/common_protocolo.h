#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <string.h>
#include <string>
#include <iostream>
#include "common_socket_connect.h"

class Protocolo {
    private:
        SocketConnect *socket;
        void enviarInt32(uint32_t num);
        void recibirInt32(uint32_t *num);
    public:
        explicit Protocolo(SocketConnect *socket);
        ~Protocolo() = default;
        Protocolo& operator>>(std::string &cadena);
        Protocolo& operator>>(uint8_t &num);
        Protocolo& operator>>(uint16_t &num);
        Protocolo& operator>>(uint32_t &num);
        Protocolo& operator<<(uint8_t &num);
        Protocolo& operator<<(uint16_t &num);
        Protocolo& operator<<(uint32_t &num);
        Protocolo& operator<<(std::string &cadena);
};

#endif
