#include "defensa.h"
#include "jugador.h"

Defensa::Defensa(int id, std::string nombre, int valor)
    : Jugador(id, nombre, valor) {}

void Defensa::mostrar_info() const { Jugador::mostrar_info(); }
