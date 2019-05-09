#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <stdexcept>
#include <exception>
#include <typeinfo>

class Error : public std::exception {
    public:
        int error_desconexion();
};

#endif
