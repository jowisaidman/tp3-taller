#include <iostream>
#include <stdexcept>
#include <exception>
#include <typeinfo>
#include "common_error.h"

int Error :: error_desconexion() {
    throw std::runtime_error("Error: la conexion fue perdida");
}
