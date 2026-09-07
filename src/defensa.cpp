#include "defensa.h"
#include "jugador.h"
#include <iostream>

Defensa::Defensa(int id, std::string nombre, int valor)
    : Jugador(id, nombre, valor) {}

void Defensa::mostrar_info() const {
    Jugador::mostrar_info();
    std::cout << "Posicion: " << posicion() << "\n";
}
std::string Defensa::posicion() const { return "Defensa"; }
