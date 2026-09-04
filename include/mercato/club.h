#pragma once

#include "jugador.h"
#include <cstddef>
#include <string>
#include <vector>

struct Club {
    Club(std::string nombre_, int presupuesto_, std::vector<Jugador *> jugadores_)
        : nombre(std::move(nombre_)), presupuesto(presupuesto_),
          jugadores(std::move(jugadores_)) {
        for (size_t i = 0; i < jugadores.size(); i++) {
            if (!jugadores[i])
                throw "jugador invalido en club";

            jugadores[i]->set_club(this);
        }
    }

    std::string nombre;
    int presupuesto;
    std::vector<Jugador *> jugadores;
};
