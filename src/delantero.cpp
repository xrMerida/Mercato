#include "delantero.h"

Delantero::Delantero(int id, std::string nombre, int valor, Club *club)
    : Jugador(id, nombre, valor, club) {}

void Delantero::mostrar_info() const { Jugador::mostrar_info(); }
