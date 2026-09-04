#include "portero.h"

Portero::Portero(int id, std::string nombre, int valor)
    : Jugador(id, nombre, valor) {}

void Portero::mostrar_info() const { Jugador::mostrar_info(); }
