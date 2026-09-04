#pragma once

#include "jugador.h"
#include <string>
#include <vector>

struct Club {
    std::string nombre;
    int presupuesto;
    std::vector<Jugador *> jugadores;
};
