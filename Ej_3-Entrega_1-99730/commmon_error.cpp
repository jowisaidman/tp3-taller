#include <stdexcept>
#include <exception>
#include <typeinfo>

int error_desconexion() {//esta funcion iria dentro de donde envia y recibe el socket
    throw std::runtime_exception("Error: la conexion fue perdida");
}

void agarrar_desconexion() {//esta no deberia ir?
    try {
        error_desconexion();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
}
