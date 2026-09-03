#include "defensa.h"
#include "jugador.h"

Defensa::Defensa(int id, std::string nombre, int valor, Club *club)
    : Jugador(id, nombre, valor, club) {}

void Defensa::mostrar_info() const { Jugador::mostrar_info(); }
