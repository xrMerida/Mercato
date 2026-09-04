#pragma once

#include "jugador.h"

class Portero : public Jugador {
  public:
    Portero(int id, std::string nombre, int valor);
    ~Portero() = default;

    void mostrar_info() const override;

  private:
    int atajadas_;
    int salidas_exitosas_;
    int goles_recibidos_;
};
