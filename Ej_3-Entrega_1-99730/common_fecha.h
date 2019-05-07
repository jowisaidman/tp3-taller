#ifndef FECHA_H
#define FECHA
#include <ctime>
#include <iostream>
#include <string>
#include <chrono>
#include <map>

class Fecha {
    private:
        std::map<int,std::string> meses;
        std::map<std::string,int> dias_por_mes;
        std::tm* fecha_actual;
        std::chrono::system_clock::time_point t_actual;
        std::string getNombreDelMes(int &numero);
        void armarMapMeses();

    public:
        Fecha();
        ~Fecha();
        //Devuelve la fecha actual.
        std::string getFechaActual();

        //Devuelve la fecha 30 dias despues de la fecha actual
        std::string getFecha30DiasDespues();
};

#endif
