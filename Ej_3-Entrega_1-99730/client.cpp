#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "common_hash.h"
#include "common_rsa.h"
#include "common_claves.h"
#include "client_request.h"
#include "client_clave_server.h"
#include "common_socket_connect.h"
#include "common_protocolo.h"
#include "client_comando.h"
#include "client_archivo_certificado.h"
#define ARGS_ESPERADOS 7
#define HOST 1
#define PORT 2
#define MODO 3
#define REQUEST 4
#define CLAVES_CLIENTE 5 
#define CLAVES_SERVER 6

int main(int argc, char *argv[]) {
    if (argc != ARGS_ESPERADOS) {
        std::cout << "Error: argumentos invalidos." << std::endl;
        return 0;
    }
    try {
        std::string modo = argv[MODO];

        std::string archivo_clave_cliente = argv[CLAVES_CLIENTE];
        Claves claves_cliente(archivo_clave_cliente);
        claves_cliente.parser();

        std::string archivo_clave_pub_srv = argv[CLAVES_SERVER];
        ClavePublicaServer clave_pub_server(archivo_clave_pub_srv);
        clave_pub_server.parser();

   	    SocketConnect socket_cliente;            
        if (!socket_cliente.addrinfo(argv[HOST],argv[PORT])) {
            std::cout << "Problema en addrinfo" << std::endl;
            return 0;
        }

        if (!socket_cliente.conectar()) {
            std::cout << "Problema en connectar" << std::endl;
            return 0;
        }

        ComandoCliente comando(&socket_cliente);

        if (modo == "new") {
            std::string archivo_request = argv[REQUEST];
            RequestCliente request(archivo_request);
            request.parser();
            comando.comandoNew(request,claves_cliente,
            clave_pub_server);

        } else if (modo == "revoke") {
            std::string archivo_certificado = argv[REQUEST];
            ArchivoCertificado arch_certificado(archivo_certificado);
            arch_certificado.parser();
            comando.comandoRevoke(arch_certificado,
            claves_cliente,clave_pub_server);
            
        } else {
            std::cout << "Error: argumentos invalidos." << std::endl;
            return 0;        
        }
        socket_cliente.cerrarConexion();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 0;
    } catch (...) {
        std::cout << "Ocurrio un error inesperado" << std::endl;
    }
    return 0;
}
