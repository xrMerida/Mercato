#pragma once

#include "jugador.h"

class Defensa : public Jugador {
  public:
    // Crea un defensa con su id, nombre y valor.
    Defensa(int id, std::string nombre, int valor);
    ~Defensa() = default;

    // Muestra la info base mas la posicion.
    void mostrar_info() const override;

    // Devuelve "Defensa".
    std::string posicion() const override;
};
