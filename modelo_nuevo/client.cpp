#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "common_hash.h"
#include "common_rsa.h"
#include "client_clave.h"
#include "client_request.h"
#include "client_clave_server.h"
#include "common_socket_connect.h"
#include "common_protocolo.h"
#include "client_comando.h"
#include "client_archivo_certificado.h"

int main(int argc, char *argv[]) {
    //Reviso parametros
    if (argc != 7) {
        std::cout << "Error: argumentos invalidos." << std::endl; //Ver que endl sea \n
        return 0;
    }
    std::string modo = argv[3];
    
    //Abro archivos y parseo [FALTA CHEQUEAR QUE LOS ARCHIVOS SE ABRIERON BIEN]
    std::string archivo_clave_cliente = argv[5];
    ClaveCliente claves_cliente(archivo_clave_cliente);
    claves_cliente.parser();

    std::string archivo_clave_pub_srv = argv[6];
    ClavePublicaServer clave_pub_server(archivo_clave_pub_srv);
    clave_pub_server.parser();

   	SocketConnect socket_cliente;            

   	if(!socket_cliente.addrinfo(argv[1],argv[2])) {
        std::cout << "Problema en addrinfo" << std::endl;
		return 0;
	}

	if(!socket_cliente.conectar()) {
        std::cout << "Problema en connect" << std::endl;
		return 0;
	}

    ComandoCliente comando;

    if (modo == "new") {

        std::string archivo_request = argv[4];
        RequestCliente request(archivo_request);
        request.parser();
        comando.comandoNew(socket_cliente,request,claves_cliente,clave_pub_server);

    } else if (modo == "revoke") {

        std::string archivo_certificado = argv[4];
        ArchivoCertificado arch_certificado(archivo_certificado);
        arch_certificado.parser();
        comando.comandoRevoke(socket_cliente,arch_certificado,claves_cliente,clave_pub_server);
        
    } else {
        std::cout << "Error: argumentos invalidos." << std::endl; //Ver que endl sea \n
        return 0;        
    }

    socket_cliente.cerrarConexion();
    return 0;
}
