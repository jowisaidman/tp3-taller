#include <iostream>
#include <string>           
#include "rsa.h"

int main ()
{
  unsigned int n;
  Rsa rsa;
  n = rsa.calcularRsa(420,19,253);
  std::cout << "El rsa calculado es: " << n <<std::endl;
  return 0;
}
