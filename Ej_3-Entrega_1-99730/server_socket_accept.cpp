#define _POSIX_C_SOURCE 200112L

#include "server_socket_accept.h"

SocketAccept :: SocketAccept() {
	s = 0;
	skt = 0;
	opt = 1;
}

SocketAccept :: ~SocketAccept() {
    skt = -1;
    s = -1;
}

void SocketAccept :: cerrarSocket() {
	shutdown(skt,SHUT_RDWR);
	close(skt);
}

void SocketAccept :: setHints() {
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;     
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = 0;  	
}

bool SocketAccept :: addrinfo(char *srvn) {
	setHints();
	s = getaddrinfo(NULL, srvn, &hints, &ptr);
   	if (s != 0) { 
      		printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      		return false;
   	}
   	return true;	
}

bool SocketAccept :: sktSocketAccept() {
	skt = socket(ptr->ai_family, ptr->ai_socktype,
	ptr->ai_protocol);
	if (skt == -1) {
		printf("Error: %s\n", strerror(errno));
		freeaddrinfo(ptr);
		return false;
	}
	return true;	
}

bool SocketAccept :: sktOpciones() {
	s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR,
	 &opt, sizeof(opt));
	if (s == -1) {
		printf("Error: %s\n", strerror(errno));
		close(skt);
		freeaddrinfo(ptr);
		return false;
	}
	return true;	
}

bool SocketAccept :: bindSocketAccept() {
	s = bind(skt, ptr->ai_addr, ptr->ai_addrlen);
	freeaddrinfo(ptr);
	if (s == -1) {
		printf("Error: %s\n", strerror(errno));
		close(skt);
		return false;
	}
	return true;
}

bool SocketAccept :: listenSocketAccept() {
	s = listen(skt, 20);
	if (s == -1) {
		printf("Error: %s\n", strerror(errno));
		close(skt);
		return false;
	}
	return true;
}

SocketConnect *SocketAccept :: acceptSocket() {
	int skt_aceptado = accept(skt, NULL, NULL); 
	if (skt == -1) {
		printf("Error: %s\n", strerror(errno));
		return nullptr;
	}
	return new SocketConnect(skt_aceptado);
} 

