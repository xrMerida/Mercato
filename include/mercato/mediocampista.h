#pragma once

#include "jugador.h"

class Mediocampista : public Jugador {
  public:
    // Crea un mediocampista con su id, nombre y valor.
    Mediocampista(int id, std::string nombre, int valor);
    ~Mediocampista() = default;

    // Muestra la info base mas la posicion.
    void mostrar_info() const override;

    // Devuelve "Mediocampista".
    std::string posicion() const override;
};
