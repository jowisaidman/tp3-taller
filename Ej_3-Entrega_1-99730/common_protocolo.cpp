#define UINT8_SIZE 1
#define UINT16_SIZE 2
#define UINT32_SIZE 4

#include "common_protocolo.h"
#include <arpa/inet.h>
#include <string>

Protocolo& Protocolo :: operator<<(std::string &cadena) {
	uint32_t tam = (uint32_t)cadena.size();
	char cad[50];
	strncpy(cad, cadena.data(),cadena.size());
	this->enviarInt32(tam);
	this->socket->enviarMensaje(cad,tam);
	return *this;
}

Protocolo& Protocolo :: operator>>(std::string &cadena) {
	uint32_t tam = 0;
	this->recibirInt32(&tam);
    char buffer[50];
	this->socket->recibirMensaje(buffer,tam);
	buffer[tam] = '\0';
	cadena = buffer;
	return *this;
}

Protocolo :: Protocolo(SocketConnect *socket) {
		this->socket = socket;
}

Protocolo& Protocolo :: operator>>(uint8_t &num) {
	this->socket->recibirMensaje((char*)&num,UINT8_SIZE);
	return *this;
}

Protocolo& Protocolo :: operator>>(uint16_t &num) {
	uint16_t numero_red(0);
	this->socket->recibirMensaje((char*)&numero_red,UINT16_SIZE);
	num = ntohs(numero_red);
	return *this;
}

Protocolo& Protocolo :: operator>>(uint32_t &num) {
	this->recibirInt32(&num);
	return *this;
}

Protocolo& Protocolo :: operator<<(uint8_t &num) {
	this->socket->enviarMensaje((char*)&num,UINT8_SIZE);
	return *this;
}

Protocolo& Protocolo :: operator<<(uint16_t &num) {
	uint16_t numero_red = htons(num);
	this->socket->enviarMensaje((char*)&numero_red,UINT16_SIZE);
	return *this;
}

Protocolo& Protocolo :: operator<<(uint32_t &num) {
	this->enviarInt32(num);
	return *this;
}

void Protocolo :: enviarInt32(uint32_t num) {
	uint32_t numero_red = htonl(num);
	this->socket->enviarMensaje((char*)&numero_red,UINT32_SIZE);
}

void Protocolo :: recibirInt32(uint32_t *num) {
	uint32_t numero_red(0);
	this->socket->recibirMensaje((char*)&numero_red,UINT32_SIZE);
	*num = ntohl(numero_red);
}
