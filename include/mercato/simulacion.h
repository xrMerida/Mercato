#pragma once

#include "club.h"
#include "jugador.h"
#include <vector>

class Simulacion {
  public:
    Simulacion(std::vector<Club *> clubes, int dia_final, int club_usuario);
    ~Simulacion();
    void ver_mi_club() const;
    void explorar_jugadores() const;
    void realizar_oferta();
    void revisar_ofertas() const;
    void ver_historial() const;
    void sigueinte_dia() const;

  private:
    std::vector<Club *> clubes_;
    std::vector<Jugador *> jugadores_;
    const Club *club_usuario_;
    int dia_actual_;
    const int dia_final_;
};
