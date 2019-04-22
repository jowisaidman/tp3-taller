#include <iostream>
#include <string>
#include <string.h>
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
	
	//empiezo a enviar mensaje de a partes
    //envio modo
    uint8_t m;
    if (modo == "new") {
        m = 0;
        socket_cliente.enviarMensaje(&m,1);
    } else {
        m = 1;
        socket_cliente.enviarMensaje(&m,1);
    }

    //envio nombre
    std::string nombre = certificado.getNombre();
    if (socket_cliente.enviarString(nombre) == -1) {
        std::cout << "Problema en enviar nombre" << std::endl;
        return 1;
    }

/*
    //envio modulo
    uint16_t mod = claves_cliente.getModulo();
    if (socket_cliente.enviarMensaje(&mod,2) == -1) {
            std::cout << "Problema en enviar modulo" << std::endl;
            return 1;       
    }

    //envio exponente publico
    uint8_t exp_publico = claves_cliente.getExponentePublico();
    if (socket_cliente.enviarMensaje(&exp_publico,1) == -1) {
            std::cout << "Problema en enviar exponente publico" << std::endl;
            return 1;       
    }    

    //envio fecha si es que hay
    if (certificado.ingresoFechas()) {
        std::string fecha_inicial = certificado.getFechaInicial();
        if (socket_cliente.enviarString(fecha_inicial) == -1) {
            std::cout << "Problema en enviar fecha inicial" << std::endl;
            return 1;
        }        
        std::string fecha_final = certificado.getFechaFinal();
        if (socket_cliente.enviarString(fecha_final) == -1) {
            std::cout << "Problema en enviar fecha final" << std::endl;
            return 1;
        } 
    }*/

    socket_cliente.cerrarConexion(); //deberia cerrar la conexion solo de escritura
    return 0;
}
