#include <string.h>
#include <string>
#include <iostream>
#include "common_socket_connect.h"

void SocketConnect :: set_hints_socket() {
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;     
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = 0;  	
}

SocketConnect :: SocketConnect() {
	s = -1;
	skt = -1;
}

SocketConnect :: SocketConnect(int socket) {
	s = -1;  
	skt = socket;
}

bool SocketConnect :: addrinfo(const char *hostn,const char *srvn) {
	set_hints_socket();
	s = getaddrinfo(hostn, srvn, &hints, &result);
   	if (s != 0) { 
      		printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      		return false;
   	}
   	return true;	
}

bool SocketConnect :: conectar() {
    bool conexion_establecida = false;
    for (ptr = result; ptr!=NULL && !conexion_establecida; 
   	  ptr=ptr->ai_next) {
   	    skt = socket(ptr->ai_family, ptr->ai_socktype,
   		   ptr->ai_protocol);
        if (skt == -1) {
            printf("Error: %s\n", strerror(errno));
        } else {
			s = connect(skt, ptr->ai_addr,
         	  ptr->ai_addrlen);
			if (s == -1) {
				printf("Error: %s\n", strerror(errno));
				close(skt);
			}
			conexion_establecida = (s != -1);
		}	
    }
	freeaddrinfo(result); 
	if (conexion_establecida == false) {
		return false;
	}
	return true;
}


int SocketConnect :: recibirMensaje(char *buf,int tam) {
	int recibido = 0, r= 0;
	bool el_socket_es_valido = true;
	while (recibido < tam && el_socket_es_valido) {
		r = recv(skt, &buf[recibido], tam-recibido, MSG_NOSIGNAL);
		if (r <= 0) {
			el_socket_es_valido = false;
		} else {
			recibido += r;
		}
	}
	if (el_socket_es_valido) {
		return recibido;
	} else {
		return -1;
	}
}

int SocketConnect :: enviarMensaje(char *buf,int tam) { 
	int total = 0,enviado = 0;
	bool el_socket_es_valido = true;
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

void SocketConnect :: cerrarConexion() {
	shutdown(skt, SHUT_RDWR);
} 

SocketConnect :: ~SocketConnect() {
    /*No hace nada*/
}
