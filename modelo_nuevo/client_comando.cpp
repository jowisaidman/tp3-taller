#include "client_comando.h"

ComandoCliente :: ComandoCliente() : protocolo() {
}


ComandoCliente :: ~ComandoCliente() {
    /*No hace nada*/
}

bool ComandoCliente :: enviarModo(uint8_t m,SocketConnect &socket) {
    if (this->protocolo.enviarInt8(m,socket) == -1) {
        std::cout << "Problema en enviar nombre" << std::endl;
        return false;        
    }
    return true;    
}

bool ComandoCliente :: comandoNew(SocketConnect &socket ,RequestCliente &request, ClaveCliente &claves_cliente) {
    uint8_t m = 0;
    if(!this->enviarModo(m,socket)) return false;
    std::string nombre = request.getNombre();
    if (protocolo.enviarString(nombre,socket) == -1) { //por ahi conviene una funcion string que envie de a pedazos y otra que reciba de a pedazos
        std::cout << "Problema en enviar nombre" << std::endl;
        return false;
    }

    uint16_t mod = claves_cliente.getModulo();
    if (protocolo.enviarInt16(mod,socket) == -1) {
            std::cout << "Problema en enviar modulo" << std::endl;
            return false;       
    }

    uint8_t exp_publico = claves_cliente.getExponentePublico();
    if (protocolo.enviarInt8(exp_publico,socket) == -1) {
            std::cout << "Problema en enviar exponente publico" << std::endl;
            return false;       
    }

    if (request.ingresoFechas()) {
        std::string fecha_inicial = request.getFechaInicial();
        if (protocolo.enviarString(fecha_inicial,socket) == -1) {
            std::cout << "Problema en enviar fecha inicial" << std::endl;
            return false;
        }        
        std::string fecha_final = request.getFechaFinal();
        if (protocolo.enviarString(fecha_final,socket) == -1) {
            std::cout << "Problema en enviar fecha final" << std::endl;
            return false;
        }
    }
    return true;
}

