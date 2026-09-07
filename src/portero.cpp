#include "portero.h"
#include <iostream>

Portero::Portero(int id, std::string nombre, int valor, int atajadas,
                 int salidas_exitosas, int goles_recibidos)
    : Jugador(id, nombre, valor), atajadas_(atajadas),
      salidas_exitosas_(salidas_exitosas), goles_recibidos_(goles_recibidos) {}

void Portero::mostrar_info() const {
    Jugador::mostrar_info();
    std::cout << "Atajadas: " << atajadas_ << "\n"
              << "Salidas exitosas: " << salidas_exitosas_ << "\n"
              << "Goles recibidos: " << goles_recibidos_ << "\n"
              << "Posicion: " << posicion() << "\n";
}

std::string Portero::posicion() const { return "Portero"; }
