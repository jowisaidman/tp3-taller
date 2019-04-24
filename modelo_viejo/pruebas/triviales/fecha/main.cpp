#include <iostream>
#include <string>           
#include "common_fecha.h"

int main ()
{
  Fecha fecha;
  std::string f = fecha.getFechaActual();
  std::string f_30 = fecha.getFecha30DiasDespues();
  std::cout << f << std::endl;
  std::cout << f_30 << std::endl;
  fecha.getFechaActual();
  std::cout << f << std::endl;
  return 0;
}
