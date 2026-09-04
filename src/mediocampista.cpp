#include "mediocampista.h"

Mediocampista::Mediocampista(int id, std::string nombre, int valor)
    : Jugador(id, nombre, valor) {}

void Mediocampista::mostrar_info() const { Jugador::mostrar_info(); }
