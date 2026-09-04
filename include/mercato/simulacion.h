#pragma once

#include "club.h"
#include "jugador.h"
#include <vector>

class Simulacion {
  public:
    Simulacion(std::vector<Club *> clubes, int dia_final, int club_usuario);
    void ver_mi_club() const;

  private:
    std::vector<Club *> clubes_;
    std::vector<Jugador *> jugadores_;
    const Club *club_usuario_;
    int dia_actual_;
    const int dia_final_;
};
