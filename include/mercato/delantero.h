#pragma once

#include "jugador.h"

class Delantero : public Jugador {
  public:
    Delantero(int id, std::string nombre, int valor);
    ~Delantero() = default;

    void mostrar_info() const override;
};
