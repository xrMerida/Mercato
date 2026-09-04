#include "delantero.h"

Delantero::Delantero(int id, std::string nombre, int valor)
    : Jugador(id, nombre, valor) {}

void Delantero::mostrar_info() const { Jugador::mostrar_info(); }
