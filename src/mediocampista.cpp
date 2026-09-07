#include "mediocampista.h"
#include <iostream>

Mediocampista::Mediocampista(int id, std::string nombre, int valor)
    : Jugador(id, nombre, valor) {}

void Mediocampista::mostrar_info() const {
    Jugador::mostrar_info();
    std::cout << "Posicion: " << posicion() << "\n";
}

std::string Mediocampista::posicion() const { return "Mediocampista"; }
