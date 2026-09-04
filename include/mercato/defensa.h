#pragma once

#include "jugador.h"

class Defensa : public Jugador {
  public:
    Defensa(int id, std::string nombre, int valor);
    ~Defensa() = default;

    void mostrar_info() const override;
};
