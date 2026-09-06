#include "portero.h"
#include <iostream>

Portero::Portero(int id, std::string nombre, int valor)
    : Jugador(id, nombre, valor), atajadas_(0), salidas_exitosas_(0),
      goles_recibidos_(0) {}

void Portero::mostrar_info() const {
    Jugador::mostrar_info();
    std::cout << "Posicion: " << posicion() << "\n"
              << "Atajadas: " << atajadas_ << "\n"
              << "Salidas exitosas: " << salidas_exitosas_ << "\n"
              << "Goles recibidos: " << goles_recibidos_ << "\n";
}
std::string Portero::posicion() const { return "Portero"; }