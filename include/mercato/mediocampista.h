#pragma once

#include "jugador.h"

class Mediocampista : public Jugador {
  public:
    Mediocampista(int id, std::string nombre, int valor);
    ~Mediocampista() = default;

    void mostrar_info() const override;
};
