#ifndef RSA_H
#define RSA_H

#include <iostream>

class Rsa {
    private:
 
    public:
        Rsa();
        unsigned int calcularRsa(
            const unsigned short int &hash,
            const unsigned char &exp,
            const unsigned short int &mod);
        ~Rsa();
};

#endif
