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
	freeaddrinfo(result); //Esto se deberia hacer en el destructor?
	if (conexion_establecida == false) {
		return false;
	}
	return true;
}

int SocketConnect :: enviarString(std::string &cadena) {
	uint32_t tam = (uint32_t)cadena.size();
	char cad[50];
	//memset(cad,0,50);
	strncpy(cad, cadena.data(),cadena.size());
	int env_tam = enviarMensaje(&tam,sizeof(uint32_t));
	int env_cad =  enviarMensaje(cad,tam);
	if (env_tam == -1 or env_cad == -1) {
		return -1;
	} else {
		return env_cad;
	}	
}

int SocketConnect :: recibirString(std::string &cadena) {
	uint32_t tam = 0; //nose si estaria bien inicializarlo en 0
	char buffer[50];
	int tam_rec = recibirMensaje(&tam,sizeof(uint32_t));
	int rec = recibirMensaje(buffer,(int)tam);
	buffer[tam] = '\0';
	cadena = buffer;
	if (rec == -1 or tam_rec == -1) {
		return -1;
	} else {
		return rec;
	}
}


/*int SocketConnect :: recibirMensaje(uint8_t *n,int tam) {
	int total = 0,recivido = 0;
	bool el_socket_es_valido = true;
	char buf[50];
	while (recivido < RESPONSE_MAX_LEN && el_socket_es_valido) {
		recivido = recv(skt, &buf[recivido], RESPONSE_MAX_LEN-recivido, MSG_NOSIGNAL);
		if (recivido <= 0) {
			el_socket_es_valido = false;
		} else {
			total += recivido;
		}
	}
	memcpy(n,(uint8_t*)buf,tam);
	if (el_socket_es_valido) {
		return total;
	} else {
		return -1;
	}
}

int SocketConnect :: enviarMensaje(uint8_t *n,int tam) { //esto esta mal porque debe ser un string, podria hacr una funcoin template
	int total = 0,enviado = 0;
	bool el_socket_es_valido = true;
	char buf[50];
	memcpy((uint8_t*)buf,n,tam);
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
}*/

void SocketConnect :: cerrarConexion() {
	shutdown(skt, SHUT_RDWR);
} 

SocketConnect :: ~SocketConnect() {
    /*No hace nada*/
}