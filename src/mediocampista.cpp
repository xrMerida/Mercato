#include "mediocampista.h"

Mediocampista::Mediocampista(int id, std::string nombre, int valor,
                             Club *club)
    : Jugador(id, nombre, valor, club) {}

void Mediocampista::mostrar_info() const { Jugador::mostrar_info(); }
