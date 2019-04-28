#define UINT8_SIZE 1
#define UINT16_SIZE 2
#define UINT32_SIZE 4

#include "common_protocolo.h"
#include <arpa/inet.h>

int Protocolo :: enviarString(std::string &cadena,SocketConnect &socket) {
	uint32_t tam = (uint32_t)cadena.size();
	char cad[50];
	strncpy(cad, cadena.data(),cadena.size());//no
	int env_tam = this->enviarInt32(tam,socket);
	int env_cad =  socket.enviarMensaje(cad,tam);//cad.c_string
	if (env_tam == -1 or env_cad == -1) {
		return -1;
	} else {
		return env_cad;
	}    
}

int Protocolo :: recibirString(std::string &cadena,SocketConnect &socket) {
	uint32_t tam = 0;
	int tam_rec = this->recibirInt32(&tam,socket);
    char buffer[50];
	int rec = socket.recibirMensaje(buffer,tam);
	buffer[tam] = '\0';
	cadena = buffer;
	if (rec == -1 or tam_rec == -1) {
		return -1;
	} else {
		return rec;
	}
}

int Protocolo :: enviarInt8(uint8_t valor,SocketConnect &socket) {
    return socket.enviarMensaje((char *)&valor, UINT8_SIZE);
}

int Protocolo :: enviarInt16(uint16_t valor,SocketConnect &socket) {
	valor = htons(valor);
    return socket.enviarMensaje((char *)&valor, UINT16_SIZE);
}

int Protocolo :: enviarInt32(uint32_t valor,SocketConnect &socket) {
	valor = htonl(valor); 
    return socket.enviarMensaje((char *)&valor, UINT32_SIZE);
}

int Protocolo :: recibirInt8(uint8_t *valor,SocketConnect &socket) {
    return socket.recibirMensaje((char *)valor, UINT8_SIZE);
}

int Protocolo :: recibirInt16(uint16_t *valor,SocketConnect &socket) {
	int rta = socket.recibirMensaje((char *)valor, UINT16_SIZE);
	*valor = ntohs(*valor);
	return rta;
}

int Protocolo :: recibirInt32(uint32_t *valor,SocketConnect &socket) {
	int rta = socket.recibirMensaje((char *)valor, UINT32_SIZE); 
    *valor = ntohl(*valor);
	return rta;
}

Protocolo :: Protocolo() {

}

Protocolo :: ~Protocolo() {

}

/*
int Protocolo :: setProtocolo() {
   	if(!this->socket.addrinfo(argv[1],argv[2])) {
        std::cout << "Problema en addrinfo" << std::endl;
		return false;
	}
	if(!this->socket.conectar()) {
        std::cout << "Problema en connect" << std::endl;
		return false;
	}
    return true;
}*/