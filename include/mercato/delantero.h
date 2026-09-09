#pragma once

#include "jugador.h"

class Delantero : public Jugador {
  public:
    // Crea un delantero con su id, nombre y valor.
    Delantero(int id, std::string nombre, int valor);
    ~Delantero() = default;

    // Muestra la info base mas la posicion.
    void mostrar_info() const override;

    // Devuelve "Delantero".
    std::string posicion() const override;
};
