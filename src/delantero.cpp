#include "delantero.h"
#include <iostream>

Delantero::Delantero(int id, std::string nombre, int valor)
    : Jugador(id, nombre, valor) {}

void Delantero::mostrar_info() const {
    Jugador::mostrar_info();
    std::cout << "Posicion: " << posicion() << "\n";
}
std::string Delantero::posicion() const { return "Delantero"; }