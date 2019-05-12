#include "common_rsa.h"
#include "common_socket_connect.h"
#include "common_certificado.h"
#include "common_protocolo.h"
#include "common_claves.h"
#include "server_indice.h"
#include "server_socket_accept.h"
#include "server_aceptador_de_conexiones.h"
#include "server_comando.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Error: argumentos invalidos." << std::endl;
        return 0;
    }
    
    std::string archivo_claves = argv[2];
    Claves claves(archivo_claves);
    claves.parser();

    std::string archivo_indice = argv[3];
    Indice indice(archivo_indice);

    SocketAccept socket_accept;

    if (!socket_accept.addrinfo(argv[1])) return 1;
	
    if (!socket_accept.sktSocketAccept()) return 1;

	if (!socket_accept.sktOpciones()) return 1;		
	
    if (!socket_accept.bindSocketAccept()) return 1;
	
    if (!socket_accept.listenSocketAccept()) return 1;

    bool continuar_ejecutando = true;
    AcceptadorDeConexiones *hilo_aceptador = 
      new AcceptadorDeConexiones(socket_accept,indice,claves);
    hilo_aceptador->start();

    std::string entrada;
    while (continuar_ejecutando) {
        std::cin >> entrada;
        if (entrada == "q") continuar_ejecutando = false;
    }
    hilo_aceptador->finalizarEjecucion();
    hilo_aceptador->join();
    delete hilo_aceptador;
    
    indice.escribirArchivo();
    return 0;
}
