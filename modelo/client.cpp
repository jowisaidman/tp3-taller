#include <iostream>
#include <string>
#include <vector>
#include "common_hash.h"
#include "common_rsa.h"
#include "client_clave.h"
#include "client_certificado.h"
#include "client_clave_server.h"
#include "common_socket_connect.h"

int main(int argc, char *argv[]) {
    //Reviso parametros
    if (argc != 7) {
        std::cout << "Error: argumentos invalidos." << std::endl; //Ver que endl sea \n
        return 0;
    }
    std::string modo = argv[3];
    if (modo != "new" && modo != "revoke") {
        std::cout << "Error: argumentos invalidos." << std::endl; //Ver que endl sea \n
        return 0;        
    }
    
    //Abro archivos y parseo
    std::string archivo_clave_cliente = argv[4];
    ClaveCliente claves_cliente(archivo_clave_cliente);
    claves_cliente.parser();

    std::string archivo_clave_pub_srv = argv[5];
    ClavePublicaServer clave_pub_server(archivo_clave_pub_srv);
    clave_pub_server.parser();

    std::string archivo_certificado = argv[6];
    CertificadoCliente certificado(archivo_certificado);
    certificado.parser();

	//creo socket
   	SocketConnect socket_cliente;            

	//tomo direcciones posibles
   	if(!socket_cliente.addrinfo(argv[1],argv[2])) {
        std::cout << "Problema en addrinfo" << std::endl;
		return 0;
	}

	//conecto cliente
	if(!socket_cliente.conectar()) {
        std::cout << "Problema en connect" << std::endl;
		return 0;
	}
	
	//envio mensaje
    std::string mensaje = certificado.getNombre();
    std::cout << "el mensaje es: "<<mensaje <<std::endl;
	socket_cliente.enviarMensaje(mensaje);


    return 0;
}
