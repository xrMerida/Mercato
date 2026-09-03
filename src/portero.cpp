#include "portero.h"

Portero::Portero(int id, std::string nombre, int valor, Club *club)
    : Jugador(id, nombre, valor, club) {}

void Portero::mostrar_info() const { Jugador::mostrar_info(); }
