#include "common_rsa.h"
#include "common_socket_connect.h"
#include "common_certificado.h"
#include "common_protocolo.h"
#include "server_claves.h"
#include "server_indice.h"
#include "server_socket_accept.h"
#include "server_comando.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    //Reviso parametros
    if (argc != 4) {
        std::cout << "Error: argumentos invalidos." << std::endl; //Ver que endl sea \n
        return 0;
    }
    
    //Abro archivos, parseo y cargo en memoria datos necesarios 
    std::string archivo_claves = argv[2];
    Claves claves(archivo_claves);

    std::string archivo_indice = argv[3];
    Indice indice(archivo_indice);

    //Creo socket accept
    SocketAccept socket_accept;

   	//seteo direcciones posibles
    if (!socket_accept.addrinfo(argv[1])) return 1;
	
	//seteo socket del servidor
    if (!socket_accept.sktSocketAccept()) return 1;

	//seteo opciones
	if (!socket_accept.sktOpciones()) return 1;		
	
	//bind
    if (!socket_accept.bindSocketAccept()) return 1;
	
	//listen
    if (!socket_accept.listenSocketAccept()) return 1;

    //acepto
    SocketConnect *socket_connect = socket_accept.acceptSocket();
    if (socket_connect == nullptr) return 1;

    ComandoServidor comando;

    comando.inciarModo(*socket_connect,indice);
    //ACA YA TENDRIA QUE TENER VARIOS HILOS ACEPTANDO NUEVAS CONEXIONES, HABRAI QUE PROTEGER EL METODO ACCEPT DE SOCKET ACCCEPT

    std::cout << "termino ejecucion" << std::endl;
    socket_connect->cerrarConexion(); 
    delete socket_connect;
    indice.escribirArchivo();
    return 0;
}
