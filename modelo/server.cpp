#include "common_rsa.h"
#include "common_socket_connect.h"
#include "common_certificado.h"
#include "server_claves.h"
#include "server_indice.h"
#include "server_socket_accept.h"
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
    
    //ACA YA TENDRIA QUE TENER VARIOS HILOS ACEPTANDO NUEVAS CONEXIONES, HABRAI QUE PROTEGER EL METODO ACCEPT DE SOCKET ACCCEPT?
    //Comienzo a recibir mensaje
    //recibo modo
    uint8_t m = -1; //incio en modo invalido
    if (!socket_connect->recibirMensaje(&m,sizeof(uint8_t))) {
        std::cout << "se recibio mal en modo" << std::endl;
        delete socket_connect;
        return 1; 
    }
    //printf("se recibio el modo: %i\n",m); [BORRAR]

    if (m == 0) {
        //recibo subject
        std::string subject;
        if (!socket_connect->recibirString(subject)) {
            std::cout << "se recibio mal en modo" << std::endl;
            return 1; 
        }
        //std::cout << "Se recibio el subject: " << subject << std::endl; [BORRAR]

        //recibo modulo
        uint16_t mod = -1;
        if (!socket_connect->recibirMensaje(&mod,sizeof(uint16_t))) {
            std::cout << "se recibio mal en modulo" << std::endl;
            return 1; 
        }
        //std::cout << "Se recibio el modulo: " << mod << std::endl; [BORRAR]

        //recibo exponente
        uint16_t exp=0;
        if (!socket_connect->recibirMensaje(&exp,sizeof(uint8_t))) {
            std::cout << "se recibio mal en exponente" << std::endl;
            return 1; 
        }
        //std::cout << "Se recibio el exponente: " << exp << std::endl; [BORRAR]   

        //recibo fechas si es que las hay, si no las creo
        std::string fecha_inicial;
        std::string fecha_final;
        if (!socket_connect->recibirString(fecha_inicial)) {
            std::cout << "Se recibio mal la fecha incial" << std::endl;
            return 1;        
        }
        if (!socket_connect->recibirString(fecha_final)) {
            std::cout << "Se recibio mal la fecha final" << std::endl;
            return 1;
        }

        //std::cout << "Se recibio la fecha inicial: " << fecha_inicial << std::endl; [BORRAR]
        //std::cout << "Se recibio la fecha final: " << fecha_final << std::endl; [BORRAR]
        if (fecha_inicial == "") std::cout << "NO HAY FECHAS" << std::endl; //aca creo fechas

        uint32_t i = indice.getIndice();
        Certificado certificado(i,subject,fecha_inicial,fecha_final,mod,exp);
        certificado.parser();
        uint16_t hash = certificado.calcularHash();
        std::cout << "El hash calculado es: " << hash << std::endl;

        
    } else if (m == 1) {
        //modo revoke
    }

    socket_connect->cerrarConexion(); 
    delete socket_connect;
    indice.escribirArchivo();
    return 0;
}
