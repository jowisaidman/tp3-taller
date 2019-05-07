#ifndef ERROR_H
#define ERROR_H
#include <stdexcept>
#include <exception>
#include <typeinfo>

class Error : public std::exception {
    public:
        error_desconexion();
        agarrar_desconexion();

};

#endif
