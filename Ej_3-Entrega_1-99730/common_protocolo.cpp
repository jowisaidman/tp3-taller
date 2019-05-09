#define UINT8_SIZE 1
#define UINT16_SIZE 2
#define UINT32_SIZE 4
#define TAM 10

#include "common_protocolo.h"
#include <arpa/inet.h>
#include <string>

void obtenerTam(uint32_t &tam_total, uint32_t &r) {
	if (tam_total - r - TAM > tam_total) {
		r = tam_total%TAM;
	} else {
		r = TAM;
	}
}

Protocolo& Protocolo :: operator<<(std::string &cadena) {
	uint32_t tam = (uint32_t)cadena.size();
	uint32_t enviado = 0;
	this->enviarInt32(tam);
	while (tam > enviado) {
		char cad[TAM];
		uint32_t e = 0;
		obtenerTam(tam,e);
		strncpy(cad, cadena.data()+enviado,e);
		this->socket->enviarMensaje(cad,e);
		enviado+=e;
	}
	return *this;
}

Protocolo& Protocolo :: operator>>(std::string &cadena) {
	uint32_t tam = 0;
	uint32_t recibido = 0;
	this->recibirInt32(&tam);
	while (tam > recibido) {
		char buffer[TAM];
		uint32_t r = 0;
		obtenerTam(tam,r);
		this->socket->recibirMensaje(buffer,r);
		buffer[r] = '\0';
		cadena += buffer;
		recibido += r;
	}
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
