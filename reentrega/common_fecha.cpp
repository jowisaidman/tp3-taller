#include "common_fecha.h"
#include <string>

Fecha :: Fecha() : meses() {
    armarMapMeses();
    t_actual = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(t_actual);
    fecha_actual = std::localtime(&t);
}

Fecha :: ~Fecha() {
}

std::string Fecha :: getFechaActual() {
    int mes = fecha_actual->tm_mon + 1;
    std::string dia = std::to_string(fecha_actual->tm_mday);
    if (dia.size() == 1) dia = '0'+dia;
    std::string hora = std::to_string(fecha_actual->tm_hour);
    if (hora.size() == 1) hora = '0'+hora;
    std::string min = std::to_string(fecha_actual->tm_min);
    if (min.size() == 1) min = '0'+min;
    std::string seg = std::to_string(fecha_actual->tm_sec);
    if (seg.size() == 1) seg = '0'+ seg;
    std::string anio = std::to_string(fecha_actual->tm_year + 1900);
    return getNombreDelMes(mes) + ' ' + dia + ' ' + hora + ':' 
    + min + ':' + seg + ' ' + anio;
}

std::string Fecha :: getFecha30DiasDespues() {
    std::chrono::duration<int,std::ratio<60*60*24*30> > treinta_dias(1);
    std::chrono::system_clock::time_point en_treinta_dias = 
      t_actual+treinta_dias;
    std::time_t t = std::chrono::system_clock::to_time_t(en_treinta_dias);
    fecha_actual = std::localtime(&t);
    std::string tiempo = getFechaActual(); 
    std::chrono::system_clock::time_point t_actual = t_actual - treinta_dias;
    t = std::chrono::system_clock::to_time_t(t_actual);
    fecha_actual = std::localtime(&t);
    return tiempo;
}


std::string Fecha :: getNombreDelMes(int &numero) {
    return meses[numero];
}


void Fecha :: armarMapMeses() {
    meses[1] = "Ene";
    meses[2] = "Feb";
    meses[3] = "Mar";
    meses[4] = "Abr";
    meses[5] = "May";
    meses[6] = "Jun";
    meses[7] = "Jul";
    meses[8] = "Ago";
    meses[9] = "Sep";
    meses[10] = "Oct";
    meses[11] = "Noc";
    meses[12] = "Dic";
}
