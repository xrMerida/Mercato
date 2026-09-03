#pragma once

#include "jugador.h"

class Mediocampista : public Jugador {
  public:
    Mediocampista(int id, std::string nombre, int valor, Club *club);
    ~Mediocampista() = default;

    void mostrar_info() const override;
};
