// condition_variable::wait_for example
#include <iostream>
#include <string>
#include <string.h>
#include "common_hash.h"

int main ()
{
  Hash hash;
  std::string cad = "certificate:\n\tserial number: 11 (0x0000000b)\n\tsubject: Federico Manuel Gomez Peter\n\tissuer: Taller de programacion 1\n\tvalidity:\n\t\tnot before: Mar 28 21:33:04 2019\n\t\tnot after: May 27 21:33:04 2019\n\tsubject public key info:\n\t\tmodulus: 253 (0x00fd)\n\t\texponent: 17 (0x11)";
  hash.calcularHash(cad);
  return 0;
}
